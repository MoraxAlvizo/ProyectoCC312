#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include "linea.h"

using namespace std;

void insertarPixel(GLint x, GLint y)
{

    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

}

Linea::Linea(GLint x1,GLint y1,GLint,GLint)
{

    this -> x1 = x1;
    this -> y1 = y1;
    this -> x2 = x2;
    this -> y2 = y2;

}

Linea::~Linea()
{

    delete(this);
}

void Linea::dibujarLinea()
{

    GLint dx,dy,x,y,xFin,p;
    dx = abs(x1 - x2);
    dy = abs(y1 - y2);
    p  = 2 * dy - dx;

    if( x1 > x2)
    {
        x    = x2;
        y    = y2;
        xFin = x1;
    }
    else
    {
        x    = x1;
        y    = y1;
        xFin = x2;
    }
    glBegin(GL_POINTS);

    while(x < xFin)
    {
        x = x + 1;
        if(p < 0)
        {
            p = p + 2*dy;
        }
        else
        {
            y = y + 1;
            p = p + 2 *(dy - dx);
        }
        glVertex2i(x, y);

    }

    glEnd();

}

void Linea::imprimirPuntoInicial()
{
    cout << this -> x1 << this -> y1;
}
