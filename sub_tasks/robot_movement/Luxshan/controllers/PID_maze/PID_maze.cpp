
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <iostream>

using namespace webots;
Robot *robot = new Robot();
int TIME_STEP = 32;

Motor *leftMotor = robot->getMotor("left_motor");
Motor *rightMotor = robot->getMotor("right_motor");

DistanceSensor *ds[2];
char dsNames[2][10] = {"Wall_L","Wall_R"};


int reading[2] ={0,0};
  
double previous_error=0.0;
double kp=5; //3
double kd=0.5; //0.5
double ki=0.0;
double Integral=0.3; 


void getReading(){
    for (int i = 0; i < 2; i++) {
      if ((ds[i]->getValue()<1.3) ){
        reading[i]=0;
        }
      else{
        reading[i]=1;}
      //std::cout<<"Readings "<<ds[i]->getValue()<<std::endl; 
      //std::cout<<"Readings "<<reading[i]<<std::endl; 
      } 
      return;    
}  

double PID(){
    double error = 0.0;
    int coefficient[2]= {-1000,1000};
 
    for (int i = 0; i < 2; i++) {
      error += coefficient[i]*reading[i];
      } 
    double P = kp*error;
    double I = Integral+(ki*error);
    double D = kd*(error-previous_error);
    
    double correction = (P+I+D)/1000;
    double l_speed = 10+correction;
    double r_speed = 10-correction;
    
    if (l_speed<0.0)  {l_speed=0;}
    if (l_speed>10.0) {l_speed=10.0;}
    if (r_speed<0.0)  {r_speed=0;}
    if (r_speed>10.0) {r_speed=10.0;}
    
    leftMotor->setVelocity(l_speed);
    rightMotor->setVelocity(r_speed);
    //std::cout << "l_speed,r_speed" <<l_speed<<" "<<r_speed<<std::endl;
      
    Integral = I;
    previous_error = error;
    //std::cout << "Integral, previous_error" <<I<<"  "<<error<<std::endl;
  
  
    return 0;
  
  }

int main(int argc, char **argv) {

 for (int i = 0; i < 2; i++) {
    ds[i] = robot->getDistanceSensor(dsNames[i]);
    ds[i]->enable(TIME_STEP);
  }
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  
  leftMotor->setVelocity(0.0);
  rightMotor->setVelocity(0.0); 
  
  while (robot->step(TIME_STEP) != -1) {
    getReading();
    PID();
  };

  delete robot;
  return 0;
}


