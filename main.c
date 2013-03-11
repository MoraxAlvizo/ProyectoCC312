#include <GL/glut.h>

void init(void);
void lineSimple(void);
void polilinea(void);
void polilineaCerrada(void);


int main(int argc, char** argv){

    glutInit(&argc,argv);   //inicializa glut
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // establece modo de visualizacion
    glutInitWindowPosition(50,100); // posicion de la ventana
    glutInitWindowSize(400,300);
    glutCreateWindow("ejemplo de opengl");
    init();
    glutDisplayFunc(polilineaCerrada);
    glutMainLoop();
    return EXIT_SUCCESS;
}

void init(void){

    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0 , 200.0, 0.0 , 150.0);
}


void lineSimple(void){

    glClear(GL_COLOR_BUFFER_BIT); // borra la ventana de visualizacion
    glColor3f(1.0,0.0,0.0);

    glBegin(GL_LINES);
        glVertex2i(0, 0);
        glVertex2i(10,145);
    glEnd();

    glFlush(); // procesa las subrutinas tan rapido como se pueda

}

void polilinea(void){

    glClear(GL_COLOR_BUFFER_BIT); // borra la ventana de visualizacion
    glColor3f(1.0,0.0,0.0);

    glBegin(GL_LINE_STRIP);
        glVertex2i(0, 0);
        glVertex2i(10,145);
        glVertex2i(0, 100);
        glVertex2i(100,145);
    glEnd();

    glFlush(); // procesa las subrutinas tan rapido como se pueda

}

void polilineaCerrada(void){

    glClear(GL_COLOR_BUFFER_BIT); // borra la ventana de visualizacion
    glColor3f(1.0,0.0,0.0);

    glBegin(GL_LINE_LOOP);
        glVertex2i(0, 0);
        glVertex2i(0, 20);
        glVertex2i(20, 20);
        glVertex2i(20, 0);
    glEnd();

    glFlush(); // procesa las subrutinas tan rapido como se pueda

}


