#ifndef TOOLSMENU_H
#define TOOLSMENU_H

#include <gtkmm.h>
#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>

enum{
    LINE,
    CIRCLE,
    ELIPSE,
    TRIANGULE,
    RECTANGULE,
    PENTAGONO,
    HEXAGONO,
    HEPTAGONO,
    SPLINE,
    PENCIL,
    SPRAY,
    ERASER,
    FLOOD,
    RECORTAR
};

class ToolsMenu:
    public Gtk::HBox
{
    public:
        ToolsMenu(bool, Gtk::Button*, Gtk::Button*, Gtk::Button*);
        virtual ~ToolsMenu();
        /** Members **/
        int figura;
        GLfloat color[3];
        GLfloat* getColor ();

    protected:

        /** Botones **/
        Gtk::Button bLine;
        Gtk::Button bCircle;
        Gtk::Button bElipse;
        Gtk::Button bTriangulo;
        Gtk::Button bRectangule;
        Gtk::Button bPentagono;
        Gtk::Button bHexagono;
        Gtk::Button bHeptagono;
        Gtk::Button bSpline;
        Gtk::Button bPencil;
        Gtk::Button bSpray;
        Gtk::Button bEraser;
        Gtk::Button bFlood;
        Gtk::Button bRecortar;
        Gtk::Image* m_image;
        Gtk::ColorButton colorWhell;


        /** Metodos **/
        void onButtonLine();
        void onButtonCircle();
        void onButtonEllipse ();
        void onButtonTriangule ();
        void onButtonRectangule ();
        void onButtonPentagono ();
        void onButtonHexagono ();
        void onButtonHeptagono ();
        void onButtonSpline ();
        void onButtonPencil ();
        void onButtonEraser ();
        void onButtonSpray ();
        void onButtonFlood ();
        void onButtonRecortar ();

};

#endif // TOOLSMENU_H
