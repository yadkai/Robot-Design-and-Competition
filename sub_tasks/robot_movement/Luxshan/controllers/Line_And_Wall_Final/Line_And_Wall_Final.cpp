#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/PositionSensor.hpp>
#include <iostream>


#define WFM_MAX_SPEED 7.25
#define WFM_TURN_POWER 2.5
#define WFM_WALL_DISTANCE 1.2
using namespace webots;

Robot *robot = new Robot();
int TIME_STEP = 32;
  
Motor *leftMotor = robot->getMotor("left_motor");
Motor *rightMotor = robot->getMotor("right_motor");  
  
DistanceSensor *ps_front = robot->getDistanceSensor("Wall_F");
DistanceSensor *ps_left = robot->getDistanceSensor("Wall_L");
DistanceSensor *ps_right = robot->getDistanceSensor("Wall_R");  


PositionSensor* leftPs = robot->getPositionSensor ("left_ps");
PositionSensor* rightPs = robot->getPositionSensor ("right_ps"); 

DistanceSensor *ds[5];
char dsNames[5][10] = {"IR_3","IR_4","IR_C","IR_5","IR_6"};


int reading[5] ={0,0,0,0,0};
  
double ps_frontValue;
double ps_leftValue;
double ps_rightValue;
int walldetected;

double previous_error=0.0;
double kp=5; //5
double kd=0.9; //0.5
double ki=0.0;
double Integral=0.0; 

// robot physical parameters
float robot_width=0.101;
float wheel_radius= 0.031;
float n=((robot_width/wheel_radius)/2*3.14159265358979323846); 

void turn_90(int dir){
     
    double lpsn = leftPs->getValue();
    double rpsn = rightPs->getValue();
    
    int r_s,l_s;
    
    if(dir==1){ r_s=-5; l_s=5;}
    else{ r_s=5; l_s=-5;}
    
    
    
    while(robot->step(TIME_STEP) != -1){
        
        double leftPsVal = leftPs->getValue ();
        double rightPsVal = rightPs->getValue ();
        
        if((leftPsVal-lpsn < n) && ((rightPsVal-rpsn) < n)){
          leftMotor->setVelocity(l_s);
          rightMotor->setVelocity(r_s);}
         else{
           leftMotor->setVelocity(0);
           rightMotor->setVelocity(0);
           break;
         }       
       }
}
 
void WallFollowingModule(void)
{
    
  std::cout<<"ps_frontValue: "<<ps_frontValue<<std::endl; 
  std::cout<<"ps_leftValue: "<<ps_leftValue<<std::endl; 
  std::cout<<"ps_rightValue: "<<ps_rightValue<<std::endl;   
  std::cout<<"WALL DETECT: "<<walldetected<<std::endl; 
  
  if (walldetected == 0)
  {
    if (ps_frontValue < 1.3)
    {
       leftMotor->setVelocity(WFM_MAX_SPEED);
       rightMotor->setVelocity(WFM_MAX_SPEED);
    }
    else
    {
      walldetected = 1;
      turn_90(1);
    }
  }
  else if (ps_frontValue < 1.3)
  { 
    leftMotor->setVelocity(WFM_MAX_SPEED + WFM_TURN_POWER * ((ps_rightValue - WFM_WALL_DISTANCE) + 0.5 * (ps_rightValue - WFM_WALL_DISTANCE)));
    rightMotor->setVelocity(WFM_MAX_SPEED - WFM_TURN_POWER * ((ps_rightValue - WFM_WALL_DISTANCE) + 0.5 * (ps_rightValue - WFM_WALL_DISTANCE)));
  }
    else if (ps_frontValue > 1.3)
  {
     turn_90(1);
     //move_forward(15);
  }
}

void getReading(){
    for (int i = 0; i < 5; i++) {
      if (ds[i]->getValue() < 512){ //512
        reading[i]=0;
        std::cout << "values = "<<ds[i]->getValue()<<std::endl;
        }
      else{
        reading[i]=1;}
      }
      return;    
}  

double PID(){
    double error = 0.0;
    int coefficient[5]= {-2000,-1000,0,1000,2000};
 
    for (int i = 0; i < 5; i++) {
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
    
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum = sum + reading[i];
        }
        
    if (sum==5){
      WallFollowingModule();
      //leftMotor->setVelocity(0.0);
      //rightMotor->setVelocity(0.0);
    }    
        
    Integral = I;
    previous_error = error;
    //std::cout << "Integral, previous_error" <<I<<"  "<<error<<std::endl;
  
    return 0;
  
  }



int main(int argc, char **argv) {

 for (int i = 0; i < 5; i++) {
    ds[i] = robot->getDistanceSensor(dsNames[i]);
    ds[i]->enable(TIME_STEP);
  }
 
  walldetected = 0;
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  
  leftMotor->setVelocity(0.0);
  rightMotor->setVelocity(0.0);
  
  ps_front->enable(TIME_STEP);
  ps_left->enable(TIME_STEP);
  ps_right->enable(TIME_STEP);
  
  leftPs->enable(TIME_STEP);
  rightPs->enable(TIME_STEP);
 
    
  while (robot->step(TIME_STEP) != -1) {
    ps_frontValue = ps_front->getValue();
    ps_leftValue = ps_left->getValue();
    ps_rightValue = ps_right->getValue();
     
    //WallFollowingModule();
    getReading();
    PID();
    
  };

  delete robot;
  return 0;
}
