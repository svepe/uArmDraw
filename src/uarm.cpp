/*
* @Copyright: Copyright[2015]<Svetlin Penkov>
*      @Date: 2015-05-11
*     @Email: s.v.penkov@sms.ed.ac.uk
*      @Desc: Wraps the basic functionality of the UArm.
*/
#include "uarm.hpp"

#include <ros/ros.h>

UArm::UArm(std::string port, int baud_rate) {
  serial_port_ = std::unique_ptr<serial::Serial>(new serial::Serial(port,
                 baud_rate, serial::Timeout::simpleTimeout(10)));

  if (!serial_port_->isOpen())
    ROS_ERROR("Unable to open port %s", port.c_str());

  arm_rotation_ = 0;
  arm_stretch_ = 0;
  arm_height_ = 0;
  hand_rotation_ = 0;
  gripper_action_ = NONE;
}

void UArm::MoveWithVelocities(double v_arm_rot, double v_arm_stretch,
                              double v_arm_height, double v_hand_rotation,
                              GripperAction gripper_action) {
  arm_rotation_ += -0.5 * v_arm_rot;
  arm_stretch_ += v_arm_stretch;
  arm_height_ += v_arm_height;
  hand_rotation_ += -v_hand_rotation;
  gripper_action_ = gripper_action;

  MoveToCurrentPose();
}

void UArm::MoveToPose(double arm_rotation, double arm_stretch,
                      double arm_height, double hand_rotation,
                      GripperAction gripper_action) {
  arm_rotation_ = arm_rotation;
  arm_stretch_ = arm_stretch;
  arm_height_ = arm_height;
  hand_rotation_ = hand_rotation;
  gripper_action_ = gripper_action;

  MoveToCurrentPose();
}

void UArm::MoveToCurrentPose() {
  ValidateCurrentPose();

  data_[0] = 0xff;
  data_[1] = 0xaa;
  data_[2] = uint8_t((uint16_t(arm_rotation_) >> 8) & 0xff);
  data_[3] = uint8_t(uint16_t(arm_rotation_) & 0xff);
  data_[4] = uint8_t((uint16_t(arm_stretch_) >> 8) & 0xff);
  data_[5] = uint8_t(uint16_t(arm_stretch_) & 0xff);
  data_[6] = uint8_t((uint16_t(arm_height_) >> 8) & 0xff);
  data_[7] = uint8_t(uint16_t(arm_height_) & 0xff);
  data_[8] = uint8_t((uint16_t(hand_rotation_) >> 8) & 0xff);
  data_[9] = uint8_t(uint16_t(hand_rotation_) & 0xff);
  data_[10] = uint8_t(uint16_t(gripper_action_));

  serial_port_->write(data_, MESSEGE_LEN);
}

void UArm::ValidateCurrentPose() {
  arm_rotation_ = Saturate(arm_rotation_, ARM_ROTATION_MIN, ARM_ROTATION_MAX);
  arm_stretch_ = Saturate(arm_stretch_, ARM_STRETCH_MIN, ARM_STRETCH_MAX);
  arm_height_ = Saturate(arm_height_, ARM_HEIGHT_MIN, ARM_HEIGHT_MAX);
  hand_rotation_ = Saturate(hand_rotation_, HAND_ROTATION_MIN,
                            HAND_ROTATION_MAX);
}

double UArm::Saturate(double v, double min, double max) {
  return (v < min) ? min : ((v > max) ? max : v);
}
