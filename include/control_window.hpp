/*
* @Copyright: Copyright[2015]<Svetlin Penkov>
*      @Date: 2015-05-06
*     @Email: s.v.penkov@sms.ed.ac.uk
*      @Desc: Add file description...
*/
#ifndef CONTROL_WINDOW_HPP
#define CONTROL_WINDOW_HPP

#include <FL/Fl_Window.H>
#include <FL/Fl.H>

class ControlWindow : public Fl_Window {
 public:
  ControlWindow(int x, int y, int width, int height, const char* name);

 private:
  int HandleMouse(int e, int x, int y);
  int handle(int e);
};

#endif

