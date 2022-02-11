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
#include <iostream>
#include <cmath>
using namespace webots;
int timeStep=32;

//Robot arm lengths
#define a1 99.32  
#define a2 99.32

double x,y,z;
double Theta, Alpha,Bheta,Gamma;

Robot *robot = new Robot();

Motor *Shoulder_motor = robot->getMotor("Shoulder_Mot");
Motor *Elbow_motor = robot->getMotor("Elbow_Mot");
Motor *Trunk_motor = robot->getMotor("Trunk_Mot");
Motor *grip_r_motor = robot->getMotor("Finger_right_Mot");
//grip_r_motor->setPosition(M_PI/2);
  
Motor *grip_l_motor = robot->getMotor("Finger_left_Mot");
//grip_l_motor->setPosition(-M_PI/2);
  
// get the time step of the current world.

// All the webots classes are defined in the "webots" namespace


void arm_pick(double x, double y, double z);
void gripper(int stat);

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
  // create the Robot instance.
  

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  //  Motor *motor = robot->getMotor("motorname");
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(timeStep) != -1) {
  
  
  arm_pick(50, 75, 75);
  gripper(1);
  //arm_pick(0,0, 198);
  //gripper(1);
  
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
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}




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


void gripper(int stat){
  /*
  stat = 1 for open status
  stat = 0 for closed status
  */
  grip_r_motor->setPosition(stat*1.5);
  grip_l_motor->setPosition(stat*(-1.5));
}