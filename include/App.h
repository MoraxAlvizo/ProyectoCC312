#ifndef APP_H
#define APP_H

#include <gtkmm.h>
#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "ToolsMenu.h"
#include "drawingOpenGL.h"


class App : public Gtk::Window
{
    public:
        App();
        virtual ~App();

    protected:
        // member widgets:
        DrawingOpenGL GL;

        Gtk::VBox box;
        Gtk::Button bOpen;
        Gtk::Button bSave;
        ToolsMenu toolsMenu;
        void onButtonOpen ();
        void onButtonSave ();
};



#endif // APP_H
