#include "../include/ToolsMenu.h"

ToolsMenu::ToolsMenu(bool flag):
    VBox(flag, 8),
    bLine("Line"),
    bCircle("Circle"),
    bElipse("Elipse"),
    bTriangulo("Triangule"),
    bRectangule("Rectangule"),
    bPentagono("Pentagono"),
    bHexagono("Hexagono"),
    bHeptagono("Heptagono")

{
    Gtk::Image *image = new Gtk::Image("line.png");


    bLine.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonLine));
    bCircle.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonCircle));
    bElipse.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonEllipse));
    bTriangulo.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonTriangule));
    bRectangule.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonRectangule));
    bPentagono.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonPentagono));
    bHexagono.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonHexagono));
    bHeptagono.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonHeptagono));
    bSpline.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonSpline));

    bLine.set_image_position(Gtk::POS_LEFT);
    bLine.set_image(*image);
    bLine.show();

    pack_start(bLine);
    pack_start(bCircle);
    pack_start(bElipse);
    pack_start(bTriangulo);
    pack_start(bRectangule);
    pack_start(bPentagono);
    pack_start(bHexagono);
    pack_start(bHeptagono);
    pack_start(bSpline);

}

ToolsMenu::~ToolsMenu()
{
    //dtor
}

void ToolsMenu::onButtonLine()
{
    figura = LINE;
}

void ToolsMenu::onButtonCircle()
{
    figura = CIRCLE;
}

void ToolsMenu::onButtonEllipse()
{
    figura = ELIPSE;
}

void ToolsMenu::onButtonTriangule()
{
    figura = TRIANGULE;
}

void ToolsMenu::onButtonRectangule ()
{
    figura = RECTANGULE;
}

void ToolsMenu::onButtonPentagono ()
{
    figura = PENTAGONO;
}

void ToolsMenu::onButtonHexagono ()
{
    figura = HEXAGONO;
}

void ToolsMenu::onButtonHeptagono ()
{
    figura = HEPTAGONO;
}

void ToolsMenu::onButtonSpline ()
{
    figura = SPLINE;
}
