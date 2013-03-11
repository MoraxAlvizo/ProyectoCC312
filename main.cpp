#include <GL/glut.h>
#include "linea.h"


#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLubyte rojo[] = {255, 0, 0, 255};
GLubyte verde[] = {0, 255, 0, 255};
GLubyte azul[] = {0, 0, 255, 255};
GLubyte blanco[] = {255, 255, 255, 255};
GLubyte negro[] = {0, 0, 0, 255};
GLubyte naranja[] = {255, 255, 0, 255};
GLubyte morado[] = {255, 0, 255, 255};

GLfloat v0[] = { -1.0f, -1.0f,  1.0f };
GLfloat v1[] = {  1.0f, -1.0f,  1.0f };
GLfloat v2[] = {  1.0f,  1.0f,  1.0f };
GLfloat v3[] = { -1.0f,  1.0f,  1.0f };
GLfloat v4[] = { -1.0f, -1.0f, -1.0f };
GLfloat v5[] = {  1.0f, -1.0f, -1.0f };
GLfloat v6[] = {  1.0f,  1.0f, -1.0f };
GLfloat v7[] = { -1.0f,  1.0f, -1.0f };

int main (int argc, char *argv[]) {
	SDL_Event evento;
	SDLKey key;

	if (SDL_Init (SDL_INIT_VIDEO) < 0) {
		fprintf (stderr, "Falló al inicializar SDL\n");
		return 1;
	}

	SDL_GL_SetAttribute (SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute (SDL_GL_GREEN_SIZE, 6);
	SDL_GL_SetAttribute (SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, 1);

	if (SDL_SetVideoMode (400, 300, 16, SDL_OPENGL) == NULL) {
		fprintf (stderr, "Falló la inicialización del video\n");
		return 1;
	}

	init();

	do {
		while (SDL_PollEvent (&evento) > 0) {
			switch (evento.type) {
				case SDL_QUIT:
					SDL_Quit ();
					return 0;
					break;
				case SDL_KEYDOWN:
					key = evento.key.keysym.sym;
					/* Eventos de teclas aquí */
					break;
			}
		} /* Procesar eventos */

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0);
        //dibujarLinea(10, 	10, 	20, 	100 ); //prueba
        dibujarLinea(10, 	10, 	190, 	10  );
        dibujarLinea(190, 	10, 	190, 	140 );
        dibujarLinea(190, 	140, 	10, 	140 );
        dibujarLinea(10, 	140, 	10, 	10  );
        dibujarLinea(20, 	20, 	100, 	130 );
        dibujarLinea(100, 	130, 	180, 	20  );
        dibujarLinea(180, 	20, 	15, 	100 );
        dibujarLinea(15, 	100, 	185, 	100 );
        dibujarLinea(185, 	100, 	20, 	20  );

        glFlush();
		SDL_GL_SwapBuffers ();
		SDL_Delay (32);
	} while (1);
	return 0;
}


