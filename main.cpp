#include <GL/glut.h>
#include "linea.h"
#include "Eventos.h"


int main(int argc, char** argv)
{
    glutInit(&argc, argv);  //inicialización de GLUT
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);  //único búfer de refresco en la ventana de visualización y el modo de color RGB
    glutInitWindowPosition(50, 100); // posición inicial, esq sup izq
    glutInitWindowSize(1000, 800); // alto y ancho de la ventana en pixeles
    glutCreateWindow("Practica 2");      // creación de ventana de visualización y título de la misma
    init();
    glutDisplayFunc(dibujar); // muestra la línea en la ventana de visualización
    glutMouseFunc(onMouse);
    glutMotionFunc(onMotion);
    glutMainLoop(); // bucle infinito que comprueba entrada de disp

    return EXIT_SUCCESS;
}
