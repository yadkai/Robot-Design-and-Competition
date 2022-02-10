#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/PositionSensor.hpp>
#include <iostream>

#define MAX_SPEED 9
using namespace webots;

Robot *robot = new Robot();
int TIME_STEP = 32;
  
Motor *leftMotor = robot->getMotor("left_motor");
Motor *rightMotor = robot->getMotor("right_motor");  
 
PositionSensor* leftPs = robot->getPositionSensor ("left_ps");
PositionSensor* rightPs = robot->getPositionSensor ("right_ps"); 
  
DistanceSensor *ps_front = robot->getDistanceSensor("Wall_F");
DistanceSensor *ps_left = robot->getDistanceSensor("Wall_L");
DistanceSensor *ps_right = robot->getDistanceSensor("Wall_R");  

double ps_frontValue;
double ps_leftValue;
double ps_rightValue;
int walldetected;

// robot physical parameters
float robot_width=0.1;
float wheel_radius= 0.03;
float n=(robot_width/wheel_radius)/2*3.1416;   
 
void move_forward(double dis){
      double mov_time= dis/14;    // distance/speed
      double s_time =robot->getTime();
      
      while(robot->step(TIME_STEP) != -1){
        double c_time = robot->getTime();
        double diff = c_time-s_time;
        
        if(diff< mov_time){
          leftMotor->setVelocity(7);
          rightMotor->setVelocity(7);}
        else{
           leftMotor->setVelocity(0);
           rightMotor->setVelocity(0);
           break;}
      }      
}

void turn_90(int dir){
     move_forward(4);
    int lpsn = leftPs->getValue();
    int rpsn = rightPs->getValue();
    
    int r_s,l_s;
    
    if(dir==1){ r_s=-5; l_s=5;}
    else{ r_s=5; l_s=-5;}
    
    while(robot->step(TIME_STEP) != -1){
        double leftPsVal = leftPs->getValue ();
        double rightPsVal = rightPs->getValue ();
        
        if((leftPsVal-lpsn < n) && (rightPsVal-rpsn < n)){
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
  //  Move forward until we are 90 cm away from the wall.
     if (ps_rightValue > 1) {
       if (ps_frontValue > 1){
           if (ps_leftValue > 1){
             turn_90(1);  // left turn
             turn_90(1);
             leftMotor->setVelocity(MAX_SPEED);
             rightMotor->setVelocity(MAX_SPEED);
           }
           else {
             turn_90(1);  // lfet turn
             leftMotor->setVelocity(MAX_SPEED);
             rightMotor->setVelocity(MAX_SPEED);
           }
       }
       else{
             leftMotor->setVelocity(MAX_SPEED);
             rightMotor->setVelocity(MAX_SPEED);
       }
     }
    else{
          turn_90(-1);  // right turn
          leftMotor->setVelocity(MAX_SPEED);
          rightMotor->setVelocity(MAX_SPEED);
    }
}

int main(int argc, char **argv) {

 
  walldetected = 0;
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  
  leftMotor->setVelocity(0.0);
  rightMotor->setVelocity(0.0);
  
  ps_front->enable(TIME_STEP);
  ps_left->enable(TIME_STEP);
  ps_right->enable(TIME_STEP);
  
  leftPs->enable (TIME_STEP);
  rightPs->enable (TIME_STEP);
 
    
  while (robot->step(TIME_STEP) != -1) {
    ps_frontValue = ps_front->getValue();
    ps_leftValue = ps_left->getValue();
    ps_rightValue = ps_right->getValue();
     
    WallFollowingModule();
    
  };

  delete robot;
  return 0;
}
