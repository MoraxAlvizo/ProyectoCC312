#ifndef POINT_H
#define POINT_H

#include <GL/gl.h>
#include <GL/glu.h>

class Point
{
    public:
        /** Constructor **/
        Point();
        Point(GLint x, GLint y);
        virtual ~Point();

        /** Metodos **/
        GLint getX();
        GLint getY();
        void setX(GLint);
        void setY(GLint);
        void moveX(int);
        void moveY(int);

        /** Operadores **/
        bool operator > (Point p2);
        void operator = (Point p2);
        bool operator == (Point p2);
        void drawPoint();

        GLint x;
        GLint y;

    private:
};

#endif // POINT_H
