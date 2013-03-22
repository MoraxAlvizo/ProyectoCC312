#ifndef EVENTOS_H_INCLUDED
#define EVENTOS_H_INCLUDED

#include "linea.h"
 GLfloat z1;
int lienzo[1000][800];

void onMouse(int button, int state, int x, int y) {


    switch(button){
        case GLUT_LEFT_BUTTON:
            switch(state)
            {
                case GLUT_DOWN:
                    xi = x;
                    yi = 800-y;
                    glReadPixels(0,0,1000,800,GL_RGB,GL_UNSIGNED_BYTE,lienzo);
                    break;

            }
        default:
            return;

    }
}

void onMotion(int x, int y) {
    glDrawPixels(1000,800,GL_RGB,GL_UNSIGNED_BYTE,lienzo);
    xf = x;
    yf = 800-y;
    dibujarLinea(xi,yi,xf,yf);

}

void dibujar(){

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glFlush();
}



#endif // EVENTOS_H_INCLUDED
