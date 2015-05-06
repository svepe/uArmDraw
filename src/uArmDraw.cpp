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

#include <serial/serial.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include "uArmDraw.hpp"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

void PoseToBytes(uint16_t arm_rotation, uint16_t arm_stretch,
                 uint16_t arm_height, uint16_t hand_rotation,
                 GripperAction gripper_action, uint8_t* data) {
  data[0] = 0xff;
  data[1] = 0xaa;
  data[2] = uint8_t((arm_rotation >> 8) & 0xff);
  data[3] = uint8_t(arm_rotation & 0xff);
  data[4] = uint8_t((arm_stretch >> 8) & 0xff);
  data[5] = uint8_t(arm_stretch & 0xff);
  data[6] = uint8_t((arm_height >> 8) & 0xff);
  data[7] = uint8_t(arm_height & 0xff);
  data[8] = uint8_t((hand_rotation >> 8) & 0xff);
  data[9] = uint8_t(hand_rotation & 0xff);
  data[10] = uint8_t(gripper_action);
}

int main() {
  string port = "/dev/ttyUSB0";
  uint64_t baud = 9600;

  serial::Serial u_arm(port, baud, serial::Timeout::simpleTimeout(1000));

  if (!u_arm.isOpen())
    cerr << "Unable to open port "  << port << endl;

  uint8_t data[MESSEGE_LEN];

  PoseToBytes(0, 100, 150, 45, NONE, data);

  u_arm.write(data, MESSEGE_LEN);

  u_arm.close();

  Fl_Window b(20, 20, 400, 400, "Title for our window");
  b.show();

  while (true) {
    Fl::wait(0.1); // Duration in seconds
  }
  return 0;
}
