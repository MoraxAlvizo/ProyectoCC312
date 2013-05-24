#include <gtkmm.h>
#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

using namespace std;

#include "include/ToolsMenu.h"
#include "include/drawingOpenGL.h"
#include "include/App.h"



int main(int argc, char** argv)
{
      Gtk::Main kit(argc, argv);
      Gtk::GL::init(argc, argv);
      App simple;
      kit.run(simple);

      return 0;
}
