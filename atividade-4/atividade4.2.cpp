#include <GL/freeglut_std.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <cstdio>
#include <stdlib.h>
#include <math.h>

void drawFunction() {
    glBegin(GL_LINE_STRIP);
    for (float i = -2; i < 2; i+= 0.01) {
        float y = i*i*i;

        glVertex2f(i, y);
    }
    glEnd();
}

void render(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    drawFunction();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set clear color to black
    //gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);
}

int main(int argc, char **argv) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutInit(&argc, argv);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Circles");
    init();

    glutDisplayFunc(render);
    glutMainLoop();

    return 1;
}
