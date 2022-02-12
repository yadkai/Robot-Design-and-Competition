#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/PositionSensor.hpp>
#include <iostream>
#include <webots/Camera.hpp>

using namespace webots;
/*
#define MAX_SPEED 5     
#define robot_width 0.11 
#define wheel_radius 0.031   
double turn_90time = 3.14*(robot_width/2)/(MAX_SPEED*wheel_radius); 
*/
Robot *robot = new Robot();
int TIME_STEP = 32;
  
Motor *leftMotor = robot->getMotor("left_motor");
Motor *rightMotor = robot->getMotor("right_motor");  
 
PositionSensor* leftPs = robot->getPositionSensor ("ps_l");
PositionSensor* rightPs = robot->getPositionSensor ("ps_r"); 
  
DistanceSensor *ps_front = robot->getDistanceSensor("ds");
DistanceSensor *ps_left = robot->getDistanceSensor("ds_l");
DistanceSensor *ps_right = robot->getDistanceSensor("ds_r");  

//Camera *cm = robot->getCamera("CAM");


double ps_frontValue;
double ps_leftValue;
double ps_rightValue;

int colour_detecting(){
      int colour_num=0; 
      Camera *camera_s = robot->getCamera("CAM");
      camera_s->enable(TIME_STEP);
      camera_s ->recognitionEnable(TIME_STEP);
      /*int number_of_objects = getRecognitionNumberOfObjects(camera_s) const;
      const CameraRecognitionObject *objects = getRecognitionObjects(camera_s) const;
      
      for (int i = 0; i < number_of_objects; ++i) {
        std::cout<<objects[i].model<<std::endl;
        std::cout<<(objects[i].position[0], objects[i].position[1], objects[i].position[2])<<std::endl;
        std::cout<<(objects[i].orientation[0], objects[i].orientation[1], objects[i].orientation[2], objects[i].orientation[3])<<std::endl;
        std::cout<<(objects[i].size[0], objects[i].size[1])<<std::endl;
      }
      */
      
      const int width = camera_s->getWidth();
      const int height = camera_s->getHeight();
     
      robot->step(TIME_STEP);
          const unsigned char *image =camera_s->getImage();
          int red=0, blue=0, green=0;
          for (int i = width / 3; i < 2 * width / 3; i++) {
                for (int j = height / 2; j < 3 * height / 4; j++) {
                  red += camera_s->imageGetRed(image, width, i, j);
                  blue += camera_s->imageGetBlue(image, width, i, j);
                  green += camera_s->imageGetGreen(image, width, i, j);
                }}
                
           std::cout<<"colorred "<< red <<std::endl;
           std::cout<<"colorblue "<< blue <<std::endl;
           std::cout<<"colorgreen "<< green <<std::endl;
           //camera_s->disable();
           if (red>(blue+green)){
               colour_num = 1;}//red
           else if(blue>(red+green)){
               colour_num = 3;}//blue
           else if(green>(blue+red)){
               colour_num = 2;}//green
           else if ((red>50000) && (green>50000) && (blue<20000)){
               colour_num = 4;} // yellow color
           else if((red>50000) && (blue>50000) && (green<20000)){
               colour_num = 5;}  // magenta
           else if((blue>50000) && (green>50000) && (red<20000)){
               colour_num = 6;}  //cyan
               
           //camera_s->disable();
           std::cout<<"colornum "<< colour_num <<std::endl;
           return colour_num;
   }  
 
// robot physical parameters
float robot_width=0.115;
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
/*
void turn90(){
    double time = robot->getTime()+turn_90time;
    double current_time=0;
     
     while (robot->step(TIME_STEP) != -1) {
          current_time = robot->getTime();
          if (time>current_time){
               leftMotor->setVelocity(5.0);
               rightMotor->setVelocity(-5.0);}
          else{
          leftMotor->setVelocity(0.0);
          rightMotor->setVelocity(0.0);
               break;}
     }
}
*/

int main(int argc, char **argv) {

 
 
  leftMotor->setPosition(INFINITY);
  rightMotor->setPosition(INFINITY);
  
  leftMotor->setVelocity(0.0);
  rightMotor->setVelocity(0.0);
  
  ps_front->enable(TIME_STEP);
  ps_left->enable(TIME_STEP);
  ps_right->enable(TIME_STEP);
  
  leftPs->enable (TIME_STEP);
  rightPs->enable (TIME_STEP);
 
  //cm ->enable(TIME_STEP);
 // cm ->recognitionEnable(TIME_STEP);
  
     
  while (robot->step(TIME_STEP) != -1) {
    ps_frontValue = ps_front->getValue();
    ps_leftValue = ps_left->getValue();
    ps_rightValue = ps_right->getValue();
    leftMotor->setVelocity(10.0);
    rightMotor->setVelocity(10.0);
    
    if (ps_frontValue<400){
        leftMotor->setVelocity(0.0);
        rightMotor->setVelocity(0.0);
    }
    
    //std::cout<<"color "<< colour_detecting()<<std::endl;
    /*
    if ((leftPs->getValue()>20) && (rightPs->getValue()>20)){
 
        turn_90(1);
         std::cout<<"color "<< colour_detecting()<<std::endl;
    }*/
    
     colour_detecting();
    
    
    std::cout<<"wheel1 "<<leftPs->getValue()<<std::endl;
    std::cout<<"wheel2 "<<rightPs->getValue()<<std::endl;
    
    
   std::cout<<"ps_frontValue: "<<ps_frontValue<<std::endl; 
   std::cout<<"ps_leftValue: "<<ps_leftValue<<std::endl; 
   std::cout<<"ps_rightValue: "<<ps_rightValue<<std::endl; 
   
  
    
  };

  delete robot;
  return 0;
}
