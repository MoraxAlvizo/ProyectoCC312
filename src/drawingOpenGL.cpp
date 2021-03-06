#include "../include/drawingOpenGL.h"

DrawingOpenGL::DrawingOpenGL(ToolsMenu* menu)
{
    Glib::RefPtr<Gdk::GL::Config> glconfig;
    this->drawing = -1;
    this->primerPintado = true;
    this->menu = menu;
    this->clicks = 0;
    this->move = false;
    this->cut = NULL;


    colorBackground[R] = 1.0;
    colorBackground[G] = 1.0;
    colorBackground[B] = 1.0;

    this->add_events(Gdk::BUTTON_PRESS_MASK |
                     Gdk::BUTTON_RELEASE_MASK |
                     Gdk::BUTTON1_MOTION_MASK |
                     Gdk::EXPOSURE_MASK|
                     Gdk::ENTER_NOTIFY_MASK);
    Glib::signal_timeout().connect( sigc::mem_fun(*this, &DrawingOpenGL::on_timeout), 100);
    glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGB | Gdk::GL::MODE_SINGLE);


    if( !glconfig )
        g_assert_not_reached();

    set_gl_capability(glconfig);

}

bool DrawingOpenGL::on_timeout()
{
    // force our program to redraw the entire clock.
    Glib::RefPtr<Gdk::GL::Context>  context;
	Glib::RefPtr<Gdk::GL::Drawable> gldrawable;

    if (menu->figura == SPRAY && drawing == true)
    {

        context = get_gl_context();
        gldrawable = get_gl_drawable();

        gldrawable->gl_begin(context);
        drawWithSpray(this->x, this->y);
        glFlush();
        gldrawable -> gl_end();
    }
    return true;
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
    GLint w = get_width(), h = get_height();

	context = get_gl_context();
	gldrawable = get_gl_drawable();

    gldrawable->gl_begin(context);

	glLoadIdentity();
	glViewport (0,0, w, h);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glPointSize(2);

	glMatrixMode(GL_PROJECTION);

	gluOrtho2D(0.0, w, 0.0, h);
    glFlush();
	gldrawable->gl_end();

	glEnable(GL_LINE_STIPPLE);

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
		crearBufferPixeles();
		glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, lienzo);

	}else{
		glDrawPixels(w, h, GL_RGB, GL_UNSIGNED_BYTE, lienzo);
	}

    glFlush();
	gldrawable -> gl_end();
	return true;
}

bool DrawingOpenGL::on_button_press_event(GdkEventButton* event) {

    Glib::RefPtr<Gdk::GL::Context>  context;
	Glib::RefPtr<Gdk::GL::Drawable> gldrawable;
    GLint w = get_width(), h = get_height();
    GLfloat * pixel;

    context = get_gl_context();
	gldrawable = get_gl_drawable();
	gldrawable->gl_begin(context);

	if(figuraAnterior != menu->figura && (figuraAnterior == RECORTAR || figuraAnterior == SPLINE) ){
        glDrawPixels(w,h,GL_RGB,GL_UNSIGNED_BYTE,lienzo);
        if(cut != NULL){
            glRasterPos2i(xRectIni,yRectIni);
            glDrawPixels(abs(xInicial - xFinal), abs(yInicial - yFinal), GL_RGB, GL_UNSIGNED_BYTE, cut);
            glRasterPos2i(0,0);
        }
        this->clicks = 0;
        this->move=false;
	}

    if(this->move){
        glDrawPixels(w,h,GL_RGB,GL_UNSIGNED_BYTE,lienzo);
        glRasterPos2i(xRectIni,yRectIni);
        glDrawPixels(abs(xInicial - xFinal), abs(yInicial - yFinal), GL_RGB, GL_UNSIGNED_BYTE, cut);
        glRasterPos2i(0,0);
        this->move = true;
        this->x = 0;
        this->y = 0;
        glColor3i(120,120,120);
        recortar(0, 0);
    }

    this->x = event->x;
    this->y = h - event->y;
    this->drawing = true;


    if( (menu->figura!= SPLINE && menu->figura!=RECORTAR) || (this->clicks == 0 && !this->move) )
        glReadPixels(0,0,w,h,GL_RGB,GL_UNSIGNED_BYTE,lienzo);
    glColor3fv(menu->getColor());
    switch(menu->figura){
        case SPRAY:
            drawWithSpray(event->x, h-event->y);
            break;
        case PENCIL:
            drawWithPencil(event->x, h-event->y);
            break;
        case ERASER:
            erase(event->x, h-event->y);
            break;
        case FLOOD:
            pixel = normalize(getPixel(this->x,this->y));
            colorBackground[0]= pixel[0];
            colorBackground[1]= pixel[1];
            colorBackground[2]= pixel[2];
            flood(event->x, h-event->y);
            break;
        case RECORTAR:
            if(this->move && (this->x < xInicial || this->x > xFinal || this->y < yInicial || this->y > yFinal)){

                glDrawPixels(w,h,GL_RGB,GL_UNSIGNED_BYTE,lienzo);
                glRasterPos2i(xRectIni,yRectIni);
                glDrawPixels(abs(xInicial - xFinal), abs(yInicial - yFinal), GL_RGB, GL_UNSIGNED_BYTE, cut);
                glRasterPos2i(0,0);
                glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, lienzo);
                this->clicks = 0;
                this->move=false;

            }
            break;
    }

    glFlush();
    gldrawable -> gl_end();
    return true;
}

bool DrawingOpenGL::on_motion_notify_event(GdkEventMotion* event) {
    //Eventos del mouse
    GLint w = get_width(), h = get_height();
    GLint auxy = h - event->y;

    if(event->state & GDK_BUTTON1_MASK){

        if(menu->figura != PENCIL && menu->figura != ERASER && menu->figura != SPRAY && menu->figura != FLOOD)
            glDrawPixels(w,h,GL_RGB,GL_UNSIGNED_BYTE,lienzo);
        glColor3fv(menu->getColor());

        switch(menu->figura){
        case LINE:
            drawLine(this->x, this->y, event->x, h-event->y);
            break;
        case CIRCLE:
            drawCircle(this->x,this->y, event->x, h-event->y);
            break;
        case ELIPSE:
            drawEllipse(this->x, this->y, abs(this->x - event->x),abs(this->y  - auxy));
            break;
        case TRIANGULE:
            drawPolygon(this->x, this->y, event->x, h-event->y, 3);
            break;
        case RECTANGULE:
            drawPolygon(this->x, this->y, event->x, h-event->y, 4);
            break;
        case PENTAGONO:
            drawPolygon(this->x, this->y, event->x, h-event->y, 5);
            break;
        case HEXAGONO:
            drawPolygon(this->x, this->y, event->x, h-event->y, 6);
            break;
        case HEPTAGONO:
            drawPolygon(this->x, this->y, event->x, h-event->y, 7);
            break;
        case SPLINE:
            drawSpline(this->x, this->y, event->x, h-event->y);
            break;
        case PENCIL:
            drawWithPencil(event->x, h-event->y);
            break;
        case ERASER:
            erase(event->x, h-event->y);
            break;
        case SPRAY:
            drawWithSpray(event->x, h-event->y);
            break;
        case RECORTAR:
            glColor3i(120,120,120);
            recortar(event->x, h-event->y);
            break;
        }

        glFlush();

    }


    return true;
}

bool DrawingOpenGL::on_button_release_event(GdkEventButton* event){

    Glib::RefPtr<Gdk::GL::Context>  context;
	Glib::RefPtr<Gdk::GL::Drawable> gldrawable;
    GLint w = get_width(), h = get_height();
    GLint yReal = h - event->y;

    context = get_gl_context();
	gldrawable = get_gl_drawable();
	gldrawable->gl_begin(context);

    this->drawing = false;

    switch(menu->figura){
        case FLOOD:
            flood(event->x, h-event->y);
            break;
        case SPLINE:
            this->clicks++;
            if(this->clicks == 3)
                glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, lienzo);
            break;
        case RECORTAR:
            this->clicks++;

            if(!this->move && this->x != event->x && this->y != yReal){
                glDrawPixels(w,h,GL_RGB,GL_UNSIGNED_BYTE,lienzo);
                delete cut;
                cut = new GLint [abs(this->x - event->x)*abs(this->y - yReal)];
                glReadPixels(xRectIni, yRectIni , xRectFinal- xRectIni, yRectFinal - yRectIni, GL_RGB, GL_UNSIGNED_BYTE, cut);
                glColor3f(1.0, 1.0, 1.0);
                glBegin(GL_QUAD_STRIP);
                    glVertex2i(this->x  , this->y );
                    glVertex2i(this->x  , yReal);
                    glVertex2i(event->x , this->y );
                    glVertex2i(event->x , yReal);
                glEnd();
                glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, lienzo);
                this->move = true;
                this->x = 0;
                this->y = 0;
                glColor3i(120,120,120);
                recortar(0, 0);

            }
            else{
                this->move = false;

                glDrawPixels(w,h,GL_RGB,GL_UNSIGNED_BYTE,lienzo);
                glRasterPos2i(xRectIni,yRectIni);
                glDrawPixels(abs(xInicial - xFinal), abs(yInicial - yFinal), GL_RGB, GL_UNSIGNED_BYTE, cut);
                glRasterPos2i(0,0);
                glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, lienzo);
            }


            break;

    }

    glFlush();
    gldrawable -> gl_end();
    figuraAnterior = menu->figura;

    if( (menu->figura == SPLINE && this->clicks == 3) || (menu->figura == RECORTAR && this->clicks == 2) )
        this->clicks = 0;
    return true;
}

bool DrawingOpenGL::on_enter_notify_event(GdkEventCrossing* event){

    switch(menu->figura){
        case PENCIL:
            get_window()->set_cursor(Gdk::Cursor(Gdk::PENCIL));
            break;
        case SPRAY:
            get_window()->set_cursor(Gdk::Cursor(Gdk::SPRAYCAN));
            break;
        case ERASER:
            get_window()->set_cursor(Gdk::Cursor(Gdk::DOTBOX));
            break;
        case FLOOD:
            get_window()->set_cursor(Gdk::Cursor(Gdk::X_CURSOR ));
            break;
        case RECORTAR:
            get_window()->set_cursor(Gdk::Cursor(Gdk::CROSS));
            break;
        default:
            get_window()->set_cursor(Gdk::Cursor(Gdk::TCROSS));
        }

    return true;
}


void DrawingOpenGL::drawLine(GLint x1, GLint y1, GLint x2, GLint y2)
{
    GLint xtemp,ytemp,dx,dy,p;
    GLfloat m;

    if(x1 > x2){
        xtemp = x1;
        x1    = x2;
        x2    = xtemp;

        ytemp = y1;
        y1    = y2;
        y2    = ytemp;
    }

    if(x1 == x2){

        if(y1 > y2){
            xtemp = x1;
            x1    = x2;
            x2    = xtemp;

            ytemp = y1;
            y1    = y2;
            y2    = ytemp;
        }
        while(y1 < y2)
            dibujarPixel(x1,y1++);
    }
    else if(y1 == y2){

        while(x1 < x2)
            dibujarPixel(x1++,y1);
    }
    else{
        m = (float)(y2-y1)/(x2-x1);

        if(m > 0){
            if(m <= 1){
                dx = abs(x1 - x2);
                dy = abs(y1 - y2);
                p  = 2 * dy - dx;
                while(x1 < x2)
                {
                    x1++;
                    if(p < 0)
                    {
                        p = p + 2*dy;
                    }
                    else
                    {
                        y1 ++;
                        p = p + 2 *(dy - dx);
                    }
                    dibujarPixel(x1,y1);
                }
            }
            else{
                dx = abs(x1 - x2);
                dy = abs(y1 - y2);
                p  = 2 * dx - dy;
                while(y1 < y2)
                {
                    y1++;
                    if(p < 0)
                    {
                        p = p + 2*dx;
                    }
                    else
                    {
                        x1 ++;
                        p = p + 2 *(dx - dy);
                    }
                    dibujarPixel(x1,y1);

                }
            }
        }
        else{
            m = abs(m);
            if(m < 1){
                dx = abs(x1 - x2);
                dy = abs(y1 - y2);
                p  = 2 * dy - dx;
                while(x1 < x2)
                {
                    x1++;
                    if(p < 0)
                    {
                        p = p + 2*dy;
                    }
                    else
                    {
                        y1 --;
                        p = p + 2 *(dy - dx);
                    }
                    dibujarPixel(x1,y1);

                }
            }
            else{
                dx = abs(x1 - x2);
                dy = abs(y1 - y2);
                p  = 2 * dx - dy;
                while(y1 > y2)
                {
                    y1--;
                    if(p < 0)
                    {
                        p = p + 2*dx;
                    }
                    else
                    {
                        x1 ++;
                        p = p + 2 *(dx - dy);
                    }
                    dibujarPixel(x1,y1);

                }
            }

        }

    }// fin del else

}

void DrawingOpenGL::dibujarPixel(GLint x, GLint y){

    if(menu->figura != ERASER){
        //glPointSize(1.0);
        glBegin(GL_POINTS);
            glVertex2i(x, y);
        glEnd();
    }
    else{
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_QUAD_STRIP);
            glVertex2i(x + 10 , y + 10);
            glVertex2i(x - 10 , y + 10);
            glVertex2i(x + 10 , y - 10);
            glVertex2i(x - 10 , y - 10);
        glEnd();
    }


    //printf("%i, %i\n",x,y);

}

void DrawingOpenGL::drawCircle(GLint xc,GLint yc, GLint xf, GLint yf){

    int x,y,p;
	x = 0;
	y = sqrt( pow(xc-xf,2) + pow(yc-yf,2));
	pointsCircle(xc, yc, x, y);
	p = 1 - y;
	while(x<y)
	{
		if(p<0)
		{
			x++;
			p +=  2 * x + 1;
		}
		else{
			x++;
			y--;
			p += 2 * (x - y) + 1;
		}
		pointsCircle(xc, yc, x, y);

	}

}


void DrawingOpenGL::pointsCircle(GLint xc,GLint yc, GLint x, GLint y)
{
    dibujarPixel(xc + x, yc + y);
    dibujarPixel(xc - x, yc + y);
    dibujarPixel(xc + x, yc - y);
    dibujarPixel(xc - x, yc - y);
    dibujarPixel(xc + y, yc + x);
    dibujarPixel(xc - y, yc + x);
    dibujarPixel(xc + y, yc - x);
    dibujarPixel(xc - y, yc - x);

}

void DrawingOpenGL::drawEllipse(GLint xc,GLint yc, GLint rx, GLint ry){


	long p, px, py, x, y, ry2, rx2, tworx2, twory2;

	ry2 = ry * ry;
	rx2 = rx * rx;
	twory2 = 2 * ry2;
	tworx2 = 2 * rx2;

	//region1
	x = 0;
	y = ry;
	pointsEllipse( xc, yc, x,y);
	p = ceil(ry2 - rx2 * ry + (0.25 * rx2));
	px = 0;
	py = tworx2 * y;
	while(px < py)
	{
		x++;
		px += twory2;
		if(p >= 0)
		{
			y--;
			py  -= tworx2;
		}
		if(p<0)
			p+= ry2 + px;
		else
			p+= ry2 + px - py;
		pointsEllipse(xc, yc, x,y);

	}
	//region 2
	p = ceil(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y-1) * (y-1) - rx2 * ry2);
	while(y > 0)
	{

		y--;
		py -= tworx2;
		if(p <= 0)
		{
			x++;
			px += twory2;
		}
		if(p>0)
			p += rx2 -py;
		else
			p += rx2 -py + px;
		pointsEllipse(xc,yc,x,y);
	}
}

void DrawingOpenGL::pointsEllipse(GLint xc,GLint yc, GLint x, GLint y){

    dibujarPixel(xc + x, yc + y);
    dibujarPixel(xc - x, yc + y);
    dibujarPixel(xc + x, yc - y);
    dibujarPixel(xc - x, yc - y);
}

void DrawingOpenGL::polar(GLint x, GLint y,GLint r,GLfloat a, GLint pos){

    int radian = 180/M_PI;

    points[pos].setX(x + ceil( r * cos(a/radian)));
    points[pos].setY(y + ceil( r * sin(a/radian)));
}

void DrawingOpenGL::drawPolygon( GLint xc, GLint yc, GLint xf, GLint yf, GLint lados){

    GLint  ang = 360/ lados, l;
    GLint radio = sqrt( pow(xc-xf,2) + pow(yc-yf,2));
    GLfloat a = atan2(yf -yc, xf -xc) * 180 /M_PI;

    if(a<0)a=360+a;

    for(l = 0;l<lados;l++)
    {
        polar(xc, yc, radio, a, l);
        a+= ang;
    }
    for(l = 1;l<lados;l++){
        drawLine(points[l-1].getX(),
                 points[l-1].getY(),
                 points[l].getX(),
                 points[l].getY());
    }

    drawLine(points[0].getX(), points[0].getY() , points[lados-1].getX(), points[lados-1].getY());

}

void DrawingOpenGL::spline(){

	GLdouble time;
	GLint x, y;
	for( time = 0; time <=1.0; time +=0.001)
	{
		x = pow(1 - time,3) * points[0].getX() +
		    3*time*pow(1-time,2) * points[1].getX() +
		    3*pow(time,2)*(1-time) * points[2].getX()+
		    pow(time,3) * points[3].getX();
		y = pow(1 - time,3) * points[0].getY() +
		    3*time*pow(1-time,2) * points[1].getY() +
		    3*pow(time,2)*(1-time) * points[2].getY()+
		    pow(time,3) * points[3].getY();
		dibujarPixel(x,y);

	}

}

void DrawingOpenGL::drawSpline(GLint x, GLint y, GLint x1, GLint y1){

    switch(this->clicks){
            case 0:
                points[0].setX(x);
                points[0].setY(y);
                points[1].setX(x);
                points[1].setY(y);
                points[2].setX(x);
                points[2].setY(y);
                points[3].setX(x1);
                points[3].setY(y1);

                break;
            case 1:
                points[1].setX(x1);
                points[1].setY(y1);
                points[2].setX(x1);
                points[2].setY(y1);
                break;
            case 2:
                points[2].setX(x1);
                points[2].setY(y1);
                break;
            }
            spline();

}

void DrawingOpenGL::drawWithPencil(GLint x, GLint y){

    dibujarPixel(x,y);
    drawLine(this->x, this->y, x, y);
    this->x = x;
    this->y = y;

}

void DrawingOpenGL::erase(GLint x, GLint y){

    dibujarPixel(x,y);
    drawLine(this->x, this->y, x, y);
    this->x = x;
    this->y = y;

}

void DrawingOpenGL::drawWithSpray(GLint x, GLint y){

    int i = 0;
	int j = 0;
	this->x = x;
	this->y = y;

	for(i = x - 20; i < x + 20; i++)
	{
		for(j = y - 20; j  < y + 20; j++)
		{
			if(rand()%217 == 0)
				dibujarPixel(i, j );

		}
	}

}

void DrawingOpenGL::flood(GLint x,GLint y){


    GLfloat *pixel, *previousPixel;
    std::queue<Point*> queuePoints;
    Point *nextPoint;

    queuePoints.push(new Point(x,y));
    glColor3fv(menu->getColor());

    while(!queuePoints.empty()){

        nextPoint = queuePoints.front();
        pixel = normalize(getPixel(nextPoint->getX(),nextPoint->getY()));
        previousPixel = normalize(getPixel(nextPoint->getX() - 1,nextPoint->getY() - 1 ));

        if(compareColors(pixel, previousPixel)){

            nextPoint->drawPoint();

            queuePoints.push(new Point(nextPoint->getX()  , nextPoint->getY()+1));
            queuePoints.push(new Point(nextPoint->getX()  , nextPoint->getY()-1));
            queuePoints.push(new Point(nextPoint->getX()+1, nextPoint->getY()  ));
            queuePoints.push(new Point(nextPoint->getX()-1, nextPoint->getY()  ));

        }

        queuePoints.pop();
        delete nextPoint;
    }

}

unsigned char* DrawingOpenGL::getPixel(GLint x, GLint y){

    unsigned char* pixel = new unsigned char[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    return pixel;
}

bool DrawingOpenGL::compareColors(GLfloat * pixel, GLfloat * previousPixel){

    if( comparePixels(pixel, colorBackground) || comparePixels(previousPixel, colorBackground) )
        return true;
    else
        return false;
}

GLfloat * DrawingOpenGL::normalize(unsigned char* pixel){

    GLfloat* pixelNormalize = new GLfloat[3];

    pixelNormalize[R] = (float)pixel[R] / 255;
    pixelNormalize[G] = (float)pixel[G] / 255;
    pixelNormalize[B] = (float)pixel[B] / 255;

    return pixelNormalize;
}

bool DrawingOpenGL::comparePixels(GLfloat* pixel1, GLfloat* pixel2){

    if(pixel1[R] == pixel2[R] && pixel1[G] == pixel2[G] && pixel1[B] == pixel2[B])
        return true;
    else
        return false;
}

void DrawingOpenGL::crearBufferPixeles(){

    GLint w = get_width(), h = get_height();
    lienzo = new GLint [w*h];
}

 void DrawingOpenGL::recortar(GLint x, GLint y){
    GLint w = get_width(), h = get_height();

    if(!this->move){

        if(this->x > x){
            if(x < 0)
                xInicial = 1;
            else
                xInicial = x;
            xFinal = this->x;
        }
        else{
            if(x > w)
                xFinal = w;
            else
                xFinal = x;
            xInicial = this->x;
        }

        if(this->y > y){
            if(y < 0)
                yInicial = 1;
            else
                yInicial = y;
            yFinal = this->y;
        }
        else{
            if(y > h)
                yFinal = h-1;
            else
                yFinal = y;
            yInicial = this->y;
        }

        xRectIni = xInicial;
        yRectIni = yInicial;
        xRectFinal = xFinal;
        yRectFinal = yFinal;

    }
    else{

        diferenciaX = this->x - x;
        diferenciaY = this->y - y;

        validarArea();

        glRasterPos2f(xRectIni,yRectIni);
        glDrawPixels(abs(xInicial - xFinal), abs(yInicial - yFinal), GL_RGB, GL_UNSIGNED_BYTE, cut);
        glRasterPos2f(0,0);


    }
    glLineStipple(2, 0x00FF);
    glBegin(GL_LINES);
        // linea 1
        glVertex2i(xRectIni  , yRectIni);
        glVertex2i(xRectFinal, yRectIni);
        // linea 2
        glVertex2i(xRectIni  , yRectFinal);
        glVertex2i(xRectFinal, yRectFinal);
        //linea 3
        glVertex2i(xRectIni  , yRectIni);
        glVertex2i(xRectIni  , yRectFinal);
        //linea 4
        glVertex2i(xRectFinal, yRectFinal);
        glVertex2i(xRectFinal, yRectIni);

    glEnd();


 }

 void DrawingOpenGL::validarArea(){

    GLint w = get_width(), h = get_height();

    /** Validacion del area en las 'x' **/

    if( (xInicial - diferenciaX) < 0 ){
        xRectIni = 1;
        xRectFinal = xFinal - xInicial;
    }
    else if((xFinal - diferenciaX ) > w){
        xRectFinal = w;
        xRectIni = w - (xFinal - xInicial);
    }
    else{
        xRectIni = xInicial - diferenciaX;
        xRectFinal = xFinal - diferenciaX;
    }

    /** Validacion del area en las 'y' **/

    if( (yInicial - diferenciaY) < 0 ){
        yRectIni = 1;
        yRectFinal = yFinal - yInicial;
    }
    else if((yFinal - diferenciaY ) > h){
        yRectFinal = h-1;
        yRectIni = h - (yFinal - yInicial);
    }
    else{
        yRectIni = yInicial - diferenciaY;
        yRectFinal = yFinal - diferenciaY;
    }

 }

void DrawingOpenGL::saveImage(){

   Gtk::FileChooserDialog dialog("Save as",Gtk::FILE_CHOOSER_ACTION_SAVE);

    //Add response buttons the the dialog:
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button("Save as", Gtk::RESPONSE_OK);

    int result = dialog.run();

    //Handle the response:
    switch(result)
    {
        case Gtk::RESPONSE_OK:

            bmpManager = new BMP(get_width(),get_height());
            bmpManager->guardarBMP(dialog.get_filename().c_str());
            delete bmpManager;
            break;

    }

}

 void DrawingOpenGL::openImage(){

    GLint w = get_width(), h = get_height();
    Gtk::FileChooserDialog dialog("Open file", Gtk::FILE_CHOOSER_ACTION_OPEN);
    std::string openFile;

    //Add response buttons the the dialog:
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

    //Show the dialog and wait for a user response:
    int result = dialog.run();

    //Handle the response:
    switch(result)
    {
        case Gtk::RESPONSE_OK :
            bmpManager = new BMP(get_width(),get_height());
            openFile = dialog.get_filename();
            bmpManager->abrirBMP(openFile.c_str());
            delete bmpManager;
            break;

    }
    glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, lienzo);


 }

 void DrawingOpenGL::newImage(){

    Glib::RefPtr<Gdk::GL::Context>  context;
	Glib::RefPtr<Gdk::GL::Drawable> gldrawable;
	gint w = get_width(), h = get_height();

	context = get_gl_context();
	gldrawable = get_gl_drawable();

	if (!gldrawable->gl_begin(context)){
		g_assert_not_reached ();
	}

    glClear(GL_COLOR_BUFFER_BIT);
    primerPintado = false;
    crearBufferPixeles();
    glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, lienzo);
    delete cut;
    cut = NULL;

    glFlush();
	gldrawable -> gl_end();

 }
