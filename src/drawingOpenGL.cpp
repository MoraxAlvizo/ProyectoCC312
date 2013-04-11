#include "../include/drawingOpenGL.h"

int lastx = 0, lasty = 0;

DrawingOpenGL::DrawingOpenGL()
{
    // Configure OpenGL-capable visual.
    Glib::RefPtr<Gdk::GL::Config> glconfig;
    this->drawing = false;
    this->add_events(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::BUTTON_MOTION_MASK);
    glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGB | Gdk::GL::MODE_DOUBLE);
    set_gl_capability(glconfig);

}

DrawingOpenGL::~DrawingOpenGL()
{

}

void DrawingOpenGL::on_realize()
{
  // We need to call the base on_realize()
    Gtk::DrawingArea::on_realize();
    this-> glwindow = get_gl_drawable();

      // *** OpenGL BEGIN ***
    if (!glwindow->gl_begin(get_gl_context()))
        return;

	glClearColor(1.0, 1.0, 1.0, 0.0); // color de la ventana, blanco
    glMatrixMode(GL_PROJECTION);      //  proyección de la imagen en la ventana de visualización
    gluOrtho2D(0.0,  get_width(), 0.0,get_height()); //  proyección en 2D
}

bool DrawingOpenGL::on_expose_event(GdkEventExpose* event)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glwindow->swap_buffers();

    return true;
}

bool DrawingOpenGL::on_button_press_event(GdkEventButton* event) {
    this->x = event->x;
    this->y = event->y;
    this->drawing = true;
    glReadPixels(0,0,ANCHO,ALTO,GL_RGB,GL_UNSIGNED_BYTE,lienzo);
    return true;
}

bool DrawingOpenGL::on_motion_notify_event(GdkEventMotion* event) {
    //Eventos del mouse
    if(this->drawing && this->get_is_drawable ()){
        if(lastx != event->x || lasty != event->y){
            glDrawPixels(ANCHO,ALTO,GL_RGB,GL_UNSIGNED_BYTE,lienzo);
            glColor3f(1.0, 0.0, 0.0);
            linea(this->x, ALTO-this->y, event->x, ALTO-event->y);
            glwindow->swap_buffers();

            lastx = event->x;
            lasty = event->y;
        }
    }

    return true;
}

bool DrawingOpenGL::on_button_release_event(GdkEventButton* event){
    this->drawing = false;
    return true;
}

void DrawingOpenGL::linea(int x, int y, int xf, int yf)
{
   glBegin(GL_LINES);
     glVertex2i(x, y);
     glVertex2i(xf, yf);
   glEnd();

}
