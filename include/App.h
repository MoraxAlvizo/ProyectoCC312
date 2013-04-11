#ifndef APP_H
#define APP_H

#include <gtkmm.h>
#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "drawingOpenGL.h"


class App : public Gtk::Window
{
public:
  App();
  virtual ~App();

protected:
  // signal handlers:
  void on_button_quit_clicked();

protected:
  // member widgets:
  DrawingOpenGL GL;

  Gtk::VBox box;
  Gtk::Button buttonQuit;
};



#endif // APP_H
