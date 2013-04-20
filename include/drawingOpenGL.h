#ifndef DRAWINGOPENGL_H
#define DRAWINGOPENGL_H

#include <gtkmm.h>
#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "ToolsMenu.h"
#include "Point.h"

#define ANCHO 800
#define ALTO  600

// Simple OpenGL scene.

class DrawingOpenGL :
    public Gtk::DrawingArea,
    public Gtk::GL::Widget<DrawingOpenGL>
{
    public:
        DrawingOpenGL(ToolsMenu* );
        virtual ~DrawingOpenGL();
        bool primerPintado;
        int x,y,x1,y1;
        int drawing;
        short clicks;
        ToolsMenu* menu;


    protected:
        //atributos
        int lienzo[ANCHO][ALTO];

        void on_realize();
        virtual bool on_expose_event(GdkEventExpose* event);
        virtual bool on_button_press_event(GdkEventButton* event);
        virtual bool on_motion_notify_event(GdkEventMotion* event);
        virtual bool on_button_release_event(GdkEventButton* event);
        virtual bool on_configure_event (GdkEventConfigure*event);

        /** Line **/
        void drawLine(GLint ,GLint , GLint , GLint );
        void dibujarPixel(GLint, GLint);

        /** Circle **/
        void drawCircle(GLint ,GLint , GLint , GLint);
        void pointsCircle(GLint ,GLint , GLint , GLint);

        /** Ellipse **/
        void drawEllipse(GLint ,GLint , GLint , GLint);
        void pointsEllipse(GLint ,GLint , GLint , GLint);

        /** Polygon **/
        Point points[7];
        void polar(GLint x, GLint y,GLint r,GLfloat a, GLint pos);
        void drawPolygon( GLint xc, GLint yc,GLint xf,GLint yf ,GLint lados);

        /** Spline **/
        void drawSpline(GLint x, GLint y, GLint x1, GLint y1);
        void spline();

};


#endif // DRAWINGOPENGL_H
