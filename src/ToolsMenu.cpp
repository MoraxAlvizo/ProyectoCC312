#include "../include/ToolsMenu.h"

ToolsMenu::ToolsMenu(bool flag, Gtk::Button* bOpen, Gtk::Button* bSave):
    HBox(flag, 12)
{
    /** Inserción de iconos**/

    m_image=new Gtk::Image("icons/line.png");
    bLine.set_image_position(Gtk::POS_LEFT);
    bLine.set_image(*m_image);

    m_image=new Gtk::Image("icons/circle.png");

    bCircle.set_image_position(Gtk::POS_LEFT);
    bCircle.set_image(*m_image);

    m_image=new Gtk::Image("icons/elipse.png");

    bElipse.set_image_position(Gtk::POS_LEFT);
    bElipse.set_image(*m_image);

    m_image=new Gtk::Image("icons/triangle.png");

    bTriangulo.set_image_position(Gtk::POS_LEFT);
    bTriangulo.set_image(*m_image);

    m_image=new Gtk::Image("icons/rectangle.png");

    bRectangule.set_image_position(Gtk::POS_LEFT);
    bRectangule.set_image(*m_image);

    m_image=new Gtk::Image("icons/pentagon.png");

    bPentagono.set_image_position(Gtk::POS_LEFT);
    bPentagono.set_image(*m_image);

    m_image=new Gtk::Image("icons/hexagon.png");

    bHexagono.set_image_position(Gtk::POS_LEFT);
    bHexagono.set_image(*m_image);

    m_image=new Gtk::Image("icons/octagon.png");

    bHeptagono.set_image_position(Gtk::POS_LEFT);
    bHeptagono.set_image(*m_image);

    m_image=new Gtk::Image("icons/spline.png");

    bSpline.set_image_position(Gtk::POS_LEFT);
    bSpline.set_image(*m_image);

    m_image=new Gtk::Image("icons/pencil.png");

    bPencil.set_image_position(Gtk::POS_LEFT);
    bPencil.set_image(*m_image);

    m_image=new Gtk::Image("icons/spray.png");

    bSpray.set_image_position(Gtk::POS_LEFT);
    bSpray.set_image(*m_image);

    m_image=new Gtk::Image("icons/eraser.png");

    bEraser.set_image_position(Gtk::POS_LEFT);
    bEraser.set_image(*m_image);

    m_image=new Gtk::Image("icons/paintCan.png");

    bFlood.set_image_position(Gtk::POS_LEFT);
    bFlood.set_image(*m_image);

    m_image=new Gtk::Image("icons/cut.png");

    bRecortar.set_image_position(Gtk::POS_LEFT);
    bRecortar.set_image(*m_image);

    m_image=new Gtk::Image("icons/colorPalette.png");

    bLine.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonLine));
    bCircle.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonCircle));
    bElipse.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonEllipse));
    bTriangulo.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonTriangule));
    bRectangule.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonRectangule));
    bPentagono.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonPentagono));
    bHexagono.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonHexagono));
    bHeptagono.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonHeptagono));
    bSpline.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonSpline));
    bPencil.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonPencil));
    bEraser.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonEraser));
    bSpray.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonSpray));
    bFlood.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonFlood));
    bRecortar.signal_clicked().connect(sigc::mem_fun(*this, &ToolsMenu::onButtonRecortar));

    pack_start(bLine);
    pack_start(bCircle);
    pack_start(bElipse);
    pack_start(bTriangulo);
    pack_start(bRectangule);
    pack_start(bPentagono);
    pack_start(bHexagono);
    pack_start(bHeptagono);
    pack_start(bSpline);
    pack_start(bPencil);
    pack_start(bEraser);
    pack_start(bSpray);
    pack_start(bFlood);
    pack_start(bRecortar);
    pack_start(*bOpen);
    pack_start(*bSave);
    pack_start(*m_image);
    pack_start(colorWhell);

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

void ToolsMenu::onButtonPencil ()
{
    figura = PENCIL;
}

void ToolsMenu::onButtonEraser ()
{
    figura = ERASER;
}

void ToolsMenu::onButtonSpray ()
{
    figura = SPRAY;
}

void ToolsMenu::onButtonFlood()
{
    figura = FLOOD;
}

void ToolsMenu::onButtonRecortar()
{
    figura = RECORTAR;
}

GLfloat* ToolsMenu::getColor()
{
    Gdk::Color newColor = colorWhell.get_color();

    color[0] = newColor.get_red()  /65535.0;
    color[1] = newColor.get_green()/65535.0;
    color[2] = newColor.get_blue() /65535.0;

    return color;
}
