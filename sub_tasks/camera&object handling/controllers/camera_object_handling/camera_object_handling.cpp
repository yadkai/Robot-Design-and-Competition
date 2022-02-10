#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/PositionSensor.hpp>
#include <iostream>

int TIME_STEP = 32;
using namespace webots;

static double   leftSpeed=5;
static double   rightSpeed=5;

Robot *robot = new Robot();

void Left(){
  
  leftSpeed  = 0;
  rightSpeed = 15;
  return;
}

// Right 
void Right(){
 
  leftSpeed  = 15;
  rightSpeed = 0;
  return;
}

// Go forward 
void Forward(){
 
  leftSpeed  = 8;
  rightSpeed = 8;
  return;
}


// int color_detection(){
 // int colour_num=0; 
 // const int width = cm->getWidth();
 // const int height = cm->getHeight();
     
  
  // const unsigned char *image =cm->getImage();
  // int red=0, blue=0, green=0;
  // for (int i = width / 3; i < 2 * width / 3; i++) {
         // for (int j = height / 2; j < 3 * height / 4; j++) {
                  // red += cm->imageGetRed(image, width, i, j);
                  // blue += cm->imageGetBlue(image, width, i, j);
                  // green += cm->imageGetGreen(image, width, i, j);
             
      // }}
    // cm->disable();
    // if (red>(blue+green)){
               // colour_num = 1;}
    // else if(blue>(red+green)){
               // colour_num = 3;}
    // else if(green>(blue+red)){
               // colour_num = 2; }   
    // //cm->disable();
    // return colour_num;
// }

 

int main(int argc, char **argv) {
  Motor *leftMotor = robot->getMotor("left_motor");
  Motor *rightMotor = robot->getMotor("right_motor");
  
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
    
  leftMotor->setVelocity(0.0);
  rightMotor->setVelocity(0.0); 
  
  //line follow distance sensor
  DistanceSensor *ds[5];
  char dsNames[5][10] = {"IR_3","IR_4","IR_C","IR_5","IR_6"}; 
  for (int i = 0; i < 5; i++) {
      ds[i] = robot->getDistanceSensor(dsNames[i]);
      ds[i]->enable(TIME_STEP);
  }
  //wall follow distance sensor 
  DistanceSensor *dsuv[2];
  char dsuvNames[3][10] = {"ds_r", "ds_l", "ds"};
  for (int i = 0; i < 3; i++) {
      dsuv[i] = robot->getDistanceSensor(dsuvNames[i]);
      dsuv[i]->enable(TIME_STEP);
  }
  
  //position sensor for wheels
  PositionSensor *ps[2];
  ps[0]=robot->getPositionSensor("ps_r");
  ps[1]=robot->getPositionSensor("ps_l");
  ps[0]->enable(TIME_STEP);
  ps[1]->enable(TIME_STEP);
  

  while (robot->step(TIME_STEP) != -1) {
  
     leftMotor->setVelocity(leftSpeed);
     rightMotor->setVelocity(rightSpeed); 
    
    };
  
    delete robot;
    return 0;
 }

