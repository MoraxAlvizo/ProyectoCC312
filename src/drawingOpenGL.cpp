#include "../include/drawingOpenGL.h"

int lastx = 0, lasty = 0;

DrawingOpenGL::DrawingOpenGL()
{

    // ==============================
    //  Lienzo OpenGL
    // ==============================

    Glib::RefPtr<Gdk::GL::Config> glconfig;
    this->drawing = false;
    this->primerPintado = true;
    this->add_events(Gdk::BUTTON_PRESS_MASK |
                     Gdk::BUTTON_RELEASE_MASK |
                     Gdk::BUTTON1_MOTION_MASK |
                     Gdk::EXPOSURE_MASK);
    glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGB | Gdk::GL::MODE_SINGLE);

    if( !glconfig )
        g_assert_not_reached();

    set_gl_capability(glconfig);

}

DrawingOpenGL::~DrawingOpenGL()
{

}


void DrawingOpenGL::on_realize()
{
  // We need to call the base on_realize()
    Gtk::DrawingArea::on_realize();

}

bool DrawingOpenGL::on_configure_event(GdkEventConfigure*event){

    Glib::RefPtr<Gdk::GL::Context>  context;
	Glib::RefPtr<Gdk::GL::Drawable> gldrawable;
    gint w = get_width(), h = get_height();

	context = get_gl_context();
	gldrawable = get_gl_drawable();

    gldrawable->gl_begin(context);

	glLoadIdentity();
	glViewport (0, 0, w, h);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glPointSize(2);
	//glColor3f(color.red, color.green, color.blue);

	glMatrixMode(GL_PROJECTION);

	gluOrtho2D(0.0, w, 0.0, h);

	//pixelBase = (GLubyte*)malloc(sizeof(GLubyte));
	//siguientePixel = (GLubyte*)malloc(sizeof(GLubyte));
	//colorAsignado = (GLubyte*)malloc(sizeof(GLubyte));
    glFlush();
	gldrawable->gl_end();

	return TRUE;

}

bool DrawingOpenGL::on_expose_event(GdkEventExpose* event)
{
    Glib::RefPtr<Gdk::GL::Context>  context;
	Glib::RefPtr<Gdk::GL::Drawable> gldrawable;
	gint w = get_width(), h = get_height();

	context = get_gl_context();
	gldrawable = get_gl_drawable();

	if (!gldrawable->gl_begin(context)){
		g_assert_not_reached ();
	}

	if(primerPintado){
		glClear(GL_COLOR_BUFFER_BIT);
		primerPintado = false;
		//crear_nuevo_buffer_pixeles();
		glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, lienzo);
	}else{
		glDrawPixels(w, h, GL_RGB, GL_UNSIGNED_BYTE, lienzo);
	}
    glFlush();
	gldrawable -> gl_end();
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
    if(event->state & GDK_BUTTON1_MASK){
        glDrawPixels(ANCHO,ALTO,GL_RGB,GL_UNSIGNED_BYTE,lienzo);
        glColor3f(1.0, 0.0, 0.0);
        linea(this->x, ALTO-this->y, event->x, ALTO-event->y);
        glFlush();

        lastx = event->x;
        lasty = event->y;

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
