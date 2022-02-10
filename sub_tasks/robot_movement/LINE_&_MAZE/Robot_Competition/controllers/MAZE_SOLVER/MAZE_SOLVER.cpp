#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <iostream>


#define WFM_MAX_SPEED 7
#define WFM_TURN_POWER 0.1
#define WFM_WALL_DISTANCE 500
using namespace webots;

Robot *robot = new Robot();
int TIME_STEP = 32;
  
Motor *leftMotor = robot->getMotor("left_motor");
Motor *rightMotor = robot->getMotor("right_motor");  
  
DistanceSensor *ps_front = robot->getDistanceSensor("Wall_F");
DistanceSensor *ps_left = robot->getDistanceSensor("Wall_L");
DistanceSensor *ps_right = robot->getDistanceSensor("Wall_R");  
double ps_frontValue;
double ps_leftValue;
double ps_rightValue;
int walldetected;
 
void WallFollowingModule(void)
{
  
  //  Move forward until we are 90 cm away from the wall.
  if (walldetected == 0)
  {
   
    if (ps_frontValue > 900)
    {
      leftMotor->setVelocity(WFM_MAX_SPEED);
      rightMotor->setVelocity(WFM_MAX_SPEED);
    }
    else
    {
      walldetected = 1;
      leftMotor->setVelocity(- 0.5 * WFM_MAX_SPEED);
      rightMotor->setVelocity(WFM_MAX_SPEED);
    }
  }
  else if (ps_frontValue > 900)
  {
    leftMotor->setVelocity(WFM_MAX_SPEED + WFM_TURN_POWER * (0.5 *(ps_rightValue - WFM_WALL_DISTANCE)));
    rightMotor->setVelocity(WFM_MAX_SPEED - WFM_TURN_POWER * (0.5 *(ps_rightValue - WFM_WALL_DISTANCE)));
    
  }
    else if (ps_frontValue < 900)
  {
    leftMotor->setVelocity(0);
    rightMotor->setVelocity(WFM_MAX_SPEED);
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
  
  ps_frontValue = ps_front->getValue();
  ps_leftValue = ps_left->getValue();
  ps_rightValue = ps_right->getValue();
    
  std::cout<<"ps_frontValue: "<<ps_frontValue<<std::endl; 
  std::cout<<"ps_leftValue: "<<ps_leftValue<<std::endl; 
  std::cout<<"ps_rightValue: "<<ps_rightValue<<std::endl;   
    
  while (robot->step(TIME_STEP) != -1) {
  
    WallFollowingModule();
    
  };

  delete robot;
  return 0;
}
