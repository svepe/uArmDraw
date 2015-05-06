/*
* @Copyright: Copyright[2015]<Svetlin Penkov>
*      @Date: 2015-05-06
*     @Email: s.v.penkov@sms.ed.ac.uk
*      @Desc: A header file which contains some basic defines.
*/
#ifndef UARM_DRAW_HPP
#define UARM_DRAW_HPP

#define ARM_ROTATION_MIN        (uint8_t)-90
#define ARM_ROTATION_MAX        (uint8_t)90
#define ARM_STRETCH_MIN         (uint8_t)0
#define ARM_STRETCH_MAX         (uint8_t)210
#define ARM_HEIGHT_MIN          (uint8_t)-180
#define ARM_HEIGHT_MAX          (uint8_t)150
#define HAND_ROTATION_MIN       (uint8_t)-90
#define HAND_ROTATION_MAX       (uint8_t)90

#define MESSEGE_LEN             11
enum GripperAction {
  NONE = 0x00,
  CATCH,
  RELEASE
};

#endif
