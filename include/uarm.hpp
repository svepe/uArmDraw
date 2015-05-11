/*
* @Copyright: Copyright[2015]<Svetlin Penkov>
*      @Date: 2015-05-11
*     @Email: s.v.penkov@sms.ed.ac.uk
*      @Desc: Wraps the basic functionality of the UArm.
*/

#ifndef UARM_HPP
#define UARM_HPP

#include <memory>
#include <string>

#include <serial/serial.h>

#define ARM_ROTATION_MIN        -90.0
#define ARM_ROTATION_MAX        90.0
#define ARM_STRETCH_MIN         0.0
#define ARM_STRETCH_MAX         210.0
#define ARM_HEIGHT_MIN          -180.0
#define ARM_HEIGHT_MAX          150.0
#define HAND_ROTATION_MIN       -90.0
#define HAND_ROTATION_MAX       90.0

#define MESSEGE_LEN             11

enum GripperAction {
  NONE = 0x00,
  GRASP,
  RELEASE
};

class UArm {
 public:
  UArm() : UArm("/dev/ttyUSB0", 9600) { }
  UArm(std::string port, int baud_rate);
  ~UArm() {
    // Should close the port, but this breaks the arduino
    // serial_port_->close()
  }

  void MoveWithVelocities(double v_arm_rot, double v_arm_stretch,
                          double v_arm_height, double v_hand_rotation,
                          GripperAction gripper_action);

  void MoveToPose(double arm_rotation, double arm_stretch,
                  double arm_height, double hand_rotation,
                  GripperAction gripper_action);

 private:
  void MoveToCurrentPose();
  void ValidateCurrentPose();
  double Saturate(double v, double min, double max);

  std::unique_ptr<serial::Serial> serial_port_;

  double arm_rotation_;
  double arm_stretch_;
  double arm_height_;
  double hand_rotation_;
  GripperAction gripper_action_;

  uint8_t data_[MESSEGE_LEN];
};

#endif
