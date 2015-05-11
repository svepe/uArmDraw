/*
* @Copyright: Copyright[2015]<Svetlin Penkov>
*      @Date: 2015-05-06
*     @Email: s.v.penkov@sms.ed.ac.uk
*      @Desc: This class extends the Fl_Window in order to implement custom
*             event handling
*/

#include "control_window.hpp"

#include <iostream>
using std::cout;
using std::endl;

ControlWindow::ControlWindow(int x, int y, int width, int height,
                             const char* name)
  : Fl_Window(x, y, width, height, name) {
}

int ControlWindow::HandleMouse(int e, int x, int y) {
  return 1;
}
int ControlWindow::handle(int e) {
  cout << "Event " << e << endl;
  return 1;
}
