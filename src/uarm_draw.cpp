/*
* @Copyright: Copyright[2015]<Svetlin Penkov>
*      @Date: 2015-05-06
*     @Email: s.v.penkov@sms.ed.ac.uk
*      @Desc: This program controls an uArm robot over the serial robot,
*             in order to draw a picture.
*/
#include <iostream>
#include <cstdint>
#include <string>

#include <ros/ros.h>
#include <sensor_msgs/Joy.h>


#include "control_window.hpp"
#include "joystick_control.hpp"
#include "uarm.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

int main(int argc, char** argv) {
  // Init ROS
  ros::init(argc, argv, "uarm");
  ros::NodeHandle n("~");

  // Create a default arm object
  UArm uarm("/dev/ttyUSB0", 115200);

  // Create a joystick object
  JoystickControl joystick("/joy", n);


  // uarm.MoveToPose(0, 0, 0, 0, RELEASE);

  ros::Rate rate(100);
  while (ros::ok()) {
    // Receive joystick values
    ros::spinOnce();

    // Move with the corresponding velocities
    uarm.MoveWithVelocities(joystick.arm_rot(), joystick.arm_stretch(),
                            joystick.arm_height(), joystick.hand_rot(),
                            (joystick.grasp()) ? GRASP : RELEASE);


    rate.sleep();
  }

  return 0;
}
