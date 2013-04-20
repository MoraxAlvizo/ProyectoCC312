#ifndef LINE_H
#define LINE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <cmath>
#include "Point.h"

class Line
{
    public:
        Line();
        Line(Point i, Point f);
        virtual ~Line();

        /** Metodos **/
        void exchangePoints();
        void drawLine();

    protected:

        /** Atributos **/
        Point   i;
        Point   f;
        GLfloat m;
    private:
        int signo(int);
};

#endif // LINE_H
