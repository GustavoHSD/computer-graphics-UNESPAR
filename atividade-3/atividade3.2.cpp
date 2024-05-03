#include <GL/freeglut_std.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>

using namespace std;

void render() { 
    ifstream file("data/dino.dat"); 
    int x, y, vertexNumber, coreNumber;

    file >> coreNumber; 
    for (int i = 0; i < coreNumber; i++) { ;
        file >> vertexNumber;
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j < vertexNumber; j++) {
            file >> x >> y;  
            glVertex2f((GLfloat) x, (GLfloat) y);
        }
        glEnd();
    } 

    glFlush();
    file.close();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_RGBA);
    glutCreateWindow("Dino");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));
   
    glutDisplayFunc(render);
    glutMainLoop();

    return 1;
}
