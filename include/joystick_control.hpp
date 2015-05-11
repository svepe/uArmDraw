/*
* @Copyright: Copyright[2015]<Svetlin Penkov>
*      @Date: 2015-05-11
*     @Email: s.v.penkov@sms.ed.ac.uk
*      @Desc: The class reads a joystick and stores the required velocities.
*/

#ifndef JOYSTICK_CONTROL_HPP
#define JOYSTICK_CONTROL_HPP

#include <string>

#include <ros/ros.h>
#include <sensor_msgs/Joy.h>

class JoystickControl {
 public:
  JoystickControl(std::string topic_name, ros::NodeHandle& n) {
    sub = n.subscribe(topic_name, 10, &JoystickControl::JoyCallback, this);
  }

  double arm_rot() { return arm_rot_; }
  double arm_stretch() { return arm_stretch_; }
  double hand_rot() { return hand_rot_; }
  double arm_height() { return arm_height_; }
  bool grasp() { return grasp_; }

 private:
  void JoyCallback(const sensor_msgs::Joy::ConstPtr& msg) {
    arm_rot_ = msg->axes[0];
    arm_stretch_ = msg->axes[1];
    hand_rot_ = msg->axes[2];
    arm_height_ = msg->axes[3];
    grasp_ = msg->buttons[5];
  }

  ros::Subscriber sub;
  double arm_rot_;
  double arm_stretch_;
  double arm_height_;
  double hand_rot_;
  bool grasp_;
};
#endif
