#ifndef DRAWINGOPENGL_H
#define DRAWINGOPENGL_H

#include <gtkmm.h>
#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define ANCHO 800
#define ALTO  600

// Simple OpenGL scene.

class DrawingOpenGL :
    public Gtk::DrawingArea,
    public Gtk::GL::Widget<DrawingOpenGL>
{
    public:
        DrawingOpenGL();
        virtual ~DrawingOpenGL();
        int x,y,x1,y1;


    protected:
        //atributos
        bool drawing;
        int lienzo[ANCHO][ALTO];
        Glib::RefPtr<Gdk::GL::Drawable> glwindow;

        void on_realize();
        bool on_expose_event(GdkEventExpose* event);
        bool on_button_press_event(GdkEventButton* event);
        bool on_motion_notify_event(GdkEventMotion* event);
        bool on_button_release_event(GdkEventButton* event);
        void linea(int x, int y, int xf, int yf);

};



#endif // DRAWINGOPENGL_H
