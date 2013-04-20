#ifndef TOOLSMENU_H
#define TOOLSMENU_H

#include <gtkmm.h>
#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Line.h"

enum{
    LINE,
    CIRCLE,
    ELIPSE,
    TRIANGULE,
    RECTANGULE,
    PENTAGONO,
    HEXAGONO,
    HEPTAGONO,
    SPLINE
};

class ToolsMenu:
    public Gtk::VBox
{
    public:
        ToolsMenu(bool);
        virtual ~ToolsMenu();
        /** Members **/
        int figura;

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

    private:
};

#endif // TOOLSMENU_H
