// File:          Arm_Test.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/DistanceSensor.hpp>
#include <webots/PositionSensor.hpp>
#include <iostream>
#include <cmath>



using namespace webots;

double Theta, Alpha,Bheta,Gamma;

//Robot arm lengths
#define a1 99.32  
#define a2 99.32
int arm_in_movement;
int step;

double x,y,z;

// All the webots classes are defined in the "webots" namespace
using namespace webots;



  Robot *robot = new Robot();

  Motor *Shoulder_motor = robot->getMotor("Shoulder_Mot");
  Motor *Elbow_motor = robot->getMotor("Elbow_Mot");
  Motor *Trunk_motor = robot->getMotor("Trunk_Mot");
  
  
  Motor *grip_r_motor = robot->getMotor("Finger_right_Mot");
  Motor *grip_l_motor = robot->getMotor("Finger_left_Mot");
  
  
  
  double Shoulder_angle,Elbow_angle,Trunk_angle,Finger_right_angle,Finger_left_angle;
  
  
  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();
  
  
  PositionSensor *Shoulder_Pos = robot->getPositionSensor("Shoulder_Pos");
  PositionSensor *Elbow_Pos = robot->getPositionSensor("Elbow_Pos");
  PositionSensor *Trunk_Pos = robot->getPositionSensor("Trunk_Pos");
  
  
  PositionSensor *Finger_right_Pos = robot->getPositionSensor("Finger_right_Pos");
  PositionSensor *Finger_left_Pos = robot->getPositionSensor("Finger_left_Pos");
  
  


void arm_pick(double x, double y, double z);
void gripper(int stat);
void gripper_control(int stat);
void arm_move(double x, double y, double z);
void arm_pick(double x, double z);
void arm_place(double x, double z);



// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {

  grip_r_motor->setVelocity(1);
  grip_l_motor->setVelocity(1);

  
  
  Shoulder_Pos->enable(timeStep);
  Elbow_Pos->enable(timeStep);
  Trunk_Pos->enable(timeStep);
  Finger_right_Pos->enable(timeStep);
  Finger_left_Pos->enable(timeStep);
  
  // create the Robot instance.


  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  //  Motor *motor = robot->getMotor("motorname");
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(timeStep) != -1) {
  
    Shoulder_angle = Shoulder_Pos->getValue();
    Elbow_angle = Elbow_Pos->getValue();
    Trunk_angle = Trunk_Pos->getValue();
    Finger_right_angle = Finger_right_Pos->getValue();
    Finger_left_angle = Finger_left_Pos->getValue();
    
    
    std::cout << "Shoulder value is: " << Shoulder_angle ;
    std::cout << "Elbow value is: " << Elbow_angle ;
    std::cout << "Trunk value is: " << Trunk_angle ;
    std::cout << "Finger_right value is: " << Finger_right_angle ;
    std::cout << "Finger_left value is: " << Finger_left_angle << std::endl;
    std::cout << "Arm in movement: " << arm_in_movement << std::endl;
    std::cout << "Step count: " << step << std::endl;
  //arm_pick(10,10,10)
  
  arm_pick(90,120);
  //arm_place(90,120);
  
  /*
  if(step == 0){
  arm_move( 0, 0, 198);
  }
  else if(step ==1){
  gripper(1);
  }
  else if(step ==2){
  gripper(0);
  }
  else if(step ==3){
  gripper(1);
  }
  else if(step ==4){
  gripper(0);
  }
  else if(step == 5){
  arm_move(30,30,40);
  }
  else if(step == 6){
  arm_move(30,60,40);
  }
  else if(step ==7){
  gripper(1);
  }
  else if(step ==8){
  arm_move(50,100,40);
  }
  else if(step ==9){
  arm_move( 30, 30, 150);
  }
  else if(step == 10){
  arm_move(30,0,150);
  }
  else if(step == 11){
  gripper(0);
  }
  else if(step == 12){
  arm_move(30,50,150);
  }
  
  */
  
  //Shoulder_motor->setPosition(INFINITY);


  //std::cout << "Alpha1 value is: " << Alpha << std::endl;
  //Elbow_motor->setPosition(INFINITY);
  //Elbow_motor->setVelocity(2);
  //Trunk_motor->setPosition(INFINITY);
  //Trunk_motor->setVelocity(2);
  
  
    // Read the sensors:
    // Enter here functions to read sensor data, like:
    //  double val = ds->getValue();

    // Process sensor data here.

    // Enter here functions to send actuator commands, like:
    //  motor->setPosition(10.0);

    //std::cout << "Alpha value is: " << Alpha << std::endl;
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}

/*
void arm_pick(double x, double y, double z){
  //Theta = atan(y/x);
  Bheta = acos((x*x + y*y + z*z - a1*a1 - a2*a2)/(2*a1*a2));
  Alpha = M_PI/2 - atan(y/sqrt(x*x + z*z)) - atan((a2*sin(Bheta)/(a1 + a2*cos(Bheta))));
  Gamma = M_PI - (Bheta+Alpha);
  
  Shoulder_motor->setVelocity(1);
  Elbow_motor->setVelocity(1);
  Trunk_motor->setVelocity(1);
  
  Shoulder_motor->setPosition(Alpha);
  Elbow_motor->setPosition(Bheta);
  Trunk_motor->setPosition(Gamma);
}
*/
void gripper_control(int stat){
  if(arm_in_movement == 0){

  gripper(stat);
}
}










void gripper(int stat){
  /*
  stat = 1 for open status
  stat = 0 for closed status
  */
  
  if(stat == 1){

  grip_r_motor->setPosition(M_PI/2);
  grip_l_motor->setPosition(-M_PI/2);
  
  if((Finger_right_angle != M_PI/2) && (Finger_left_angle != -M_PI/2)){
  
  arm_in_movement = 1;
  
  }
  else if((Finger_right_angle = M_PI/2) && (Finger_left_angle = -M_PI/2)){
  
  arm_in_movement = 0;
  
  Finger_right_angle = 0;
  Finger_left_angle = 0;
  step=step+1;
  }
  }
  else if(stat == 0){
  
  grip_r_motor->setPosition(0.01);
  grip_l_motor->setPosition(-0.01);
  
  if((Finger_right_angle != 0.01) && (Finger_left_angle != -0.01)){
  
  arm_in_movement = 1;
  
  }
  else if((Finger_right_angle == 0.01) && (Finger_left_angle == -0.01)){
  
  arm_in_movement = 0;
  
  Finger_right_angle = 0;
  Finger_left_angle = 0;
  step=step+1;
  }
  }
  
  

}

void arm_move(double x, double y, double z){

  Bheta = acos((x*x + y*y + z*z - a1*a1 - a2*a2)/(2*a1*a2));
  Alpha = M_PI/2 - atan(y/sqrt(x*x + z*z)) - atan((a2*sin(Bheta)/(a1 + a2*cos(Bheta))));
  Gamma = M_PI - (Bheta+Alpha);
  
  Shoulder_motor->setVelocity(1);
  Elbow_motor->setVelocity(1);
  Trunk_motor->setVelocity(1);
  
  Shoulder_motor->setPosition(Alpha);
  Elbow_motor->setPosition(Bheta);
  Trunk_motor->setPosition(Gamma);
  
  if((Shoulder_angle != Alpha) && (Elbow_angle != Bheta) && (Trunk_angle != Gamma)){
  
  arm_in_movement = 1;
  
  }
  else if((Shoulder_angle == Alpha) && (Elbow_angle == Bheta) && (Trunk_angle == Gamma)){
  
  arm_in_movement = 0;
  

  step=step+1;
  }


}

void arm_pick(double x, double z){
if(step ==0){
  arm_move(x,70,z);
 
 }
 if(step ==1){
 gripper(1);
 }
 
 if(step ==2){
 arm_move(x,5,z);
 }
 if(step==3){
 gripper(0);
 }
 if(step==4){
 arm_move(x,70,z);
 //step=0;
 }
}


void arm_place(double x, double z){
if(step ==0){
 arm_move(x,70,z);
 }
 if(step ==1){
 arm_move(x,5,z);
 }
 
 if(step ==2){
 gripper(1);
 }
 if(step==3){
 arm_move(x,70,z);
 }
 if(step==4){
 gripper(0);
 //step=0;
 }
}
