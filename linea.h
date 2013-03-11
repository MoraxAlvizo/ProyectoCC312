#ifndef LINEA_H_INCLUDED
#define LINEA_H_INCLUDED

#include<GL/glut.h>
#include<stdio.h>
#include<stdbool.h>



void init(void)
{
   glClearColor(1.0, 1.0, 1.0, 0.0); // color de la ventana, blanco
   glMatrixMode(GL_PROJECTION);      //  proyección de la imagen en la ventana de visualización
   gluOrtho2D(0.0, 200.0, 0.0, 150.0); //  proyección en 2D
}

void lineSegment(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_POINTS);
     glVertex2i(10, 10);
   glEnd();
   glBegin(GL_POINTS);
     glVertex2i(190, 140);
   glEnd();
   glBegin(GL_LINES);
     glVertex2i(180, 15);
     glVertex2i(10, 145);
   glEnd();
   glFlush();
}


void dibujarPixel(GLint x, GLint y){

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

}


void dibujarLinea(GLint x1,GLint y1,GLint x2,GLint y2)
{

    GLint xtemp, ytemp,dx,dy,x,y,xFin,p;
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
#endif // LINEA_H_INCLUDED
