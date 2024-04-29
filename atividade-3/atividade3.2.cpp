#include <GL/freeglut_std.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));
    
    string line; 
    ifstream file("data/dino.dat"); 
    int x, y , z, w;

    glBegin(GL_LINE_STRIP);
    while (getline(file, line)) {
        file >> x >> y >> z >> w;
        glVertex2f((GLfloat) x, (GLfloat) y);
        glVertex2f((GLfloat) z, (GLfloat) w);
    } 
    glEnd(); 

    glFlush();
    file.close();
}

int main(int argc, char **argv) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutInitDisplayMode(GLUT_RGB | GLUT_RGBA);
    glutCreateWindow("Lines");
    glutDisplayFunc(render);
    glutMainLoop();

    return 1;
}
