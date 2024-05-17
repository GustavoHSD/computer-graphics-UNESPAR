#include <GL/freeglut_std.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <cstdio>
#include <stdlib.h>
#include <math.h>

struct Point {
    float x;
    float y;
};

Point click;

void drawCircle(float h, float k, float r, int num_segments) {
    glBegin(GL_LINE_STRIP);
    glVertex2f(click.x, click.y - 100);
    for(int i = 0; i < num_segments; i++) {
        float theta = 3.1415926f * float(i) / float(num_segments);

        float x = r * cosf(theta);
        float y = r * sinf(theta);

        glVertex2f(x + h, y + k);
    }
    glVertex2f(click.x, click.y - 100);
    glEnd();
    /*
    glBegin(GL_LINE_STRIP);
        glVertex2f(firstLine.x, firstLine.y);
        glVertex2f(h, k - 100);
    glEnd();
    glBegin(GL_LINE_STRIP);
        glVertex2f(secondLine.x, secondLine.y);
        glVertex2f(h, k - 100);
    glEnd();
    */

}

void render(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    drawCircle(click.x, click.y, 20, 50);
    glFlush();
}

void mouseListener(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        Point point;
        point.x = x;
        point.y = y;
        click = point;
        switch (button) {
            case GLUT_LEFT_BUTTON: 
                glutPostRedisplay();
                break;
            case GLUT_RIGHT_BUTTON: 
                glutPostRedisplay();
                break;
        }
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set clear color to black
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);
}

int main(int argc, char **argv) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutInit(&argc, argv);
    glutCreateWindow("Water drop");
    init();

    glutDisplayFunc(render);
    glutMouseFunc(mouseListener);
    glutMainLoop();

    return 1;
}
