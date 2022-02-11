#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/Camera.hpp>
#include <webots/PositionSensor.hpp>

#define TIME_STEP 64
using namespace webots;

int main(int argc, char **argv) {
  Robot *robot = new Robot();
  DistanceSensor *ds[2];
  char dsNames[2][10] = {"ds_right", "ds_left"};
  for (int i = 0; i < 2; i++) {
    ds[i] = robot->getDistanceSensor(dsNames[i]);
    ds[i]->enable(TIME_STEP);
  }
  
  Camera *cm;
  cm=robot -> getCamera("CAM");
  cm ->enable (TIME_STEP);
  cm -> recognitionEnable(TIME_STEP);
  
  //char petch_colour[3][7] ={"red","Green","blue"}; 
  
  PositionSensor *ps[2];
  ps[0]=robot->getPositionSensor("ps_1");
  ps[1]=robot->getPositionSensor("ps_2");
  ps[0]->enable(TIME_STEP);
  ps[1]->enable(TIME_STEP);
  
  Motor *wheels[4];
  char wheels_names[4][8] = {"wheel1", "wheel2", "wheel3", "wheel4"};
  for (int i = 0; i < 4; i++) {
    wheels[i] = robot->getMotor(wheels_names[i]);
    wheels[i]->setPosition(INFINITY);
    wheels[i]->setVelocity(0.0);
  }
   

  int avoidObstacleCounter = 0;
  while (robot->step(TIME_STEP) != -1) {
    double leftSpeed = 1.0;
    double rightSpeed = 1.0;
    if (avoidObstacleCounter > 0) {
      avoidObstacleCounter--;
      leftSpeed = 1.0;
      rightSpeed = -1.0;
    } else { // read sensors
      for (int i = 0; i < 2; i++) {
        if (ds[i]->getValue() < 950.0)
          avoidObstacleCounter = 100;
      }
    }
    
      int colour_num=0; 
      const int width = cm->getWidth();
      const int height = cm->getHeight();
     
      robot->step(TIME_STEP);
          const unsigned char *image =cm->getImage();
          int red=0, blue=0, green=0;
          for (int i = width / 3; i < 2 * width / 3; i++) {
                for (int j = height / 2; j < 3 * height / 4; j++) {
                  red += cm->imageGetRed(image, width, i, j);
                  blue += cm->imageGetBlue(image, width, i, j);
                  green += cm->imageGetGreen(image, width, i, j);
                
                }}
           //cm->disable();
           if (red>(blue+green)){
               colour_num = 1;}
           else if(blue>(red+green)){
               colour_num = 3;}
           else if(green>(blue+red)){
               colour_num = 2; }
            std::cout <<" " <<colour_num<< std::endl;   
           //camera_s->disable();
    
   
    wheels[0]->setVelocity(leftSpeed);
    wheels[1]->setVelocity(rightSpeed);
    wheels[2]->setVelocity(leftSpeed);
    wheels[3]->setVelocity(rightSpeed);
    
    std::cout<<"wheel1 "<<ps[0]->getValue()<<std::endl;
    std::cout<<"wheel2 "<<ps[1]->getValue()<<std::endl;
  }
  delete robot;
  return 0;  // EXIT_SUCCESS
}