#include <GL/glut.h>
#include <GL/gl.h>

void render(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);

    glPointSize(55);
    
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.1, 0.0);
        glVertex2f(0.2, 0.0);
        glVertex2f(-0.1, 0.0);
        glVertex2f(-0.2, 0.0);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
        glVertex2f(0.0, -0.1);
        glVertex2f(0.1, -0.1);
        glVertex2f(0.2, -0.1);
        glVertex2f(-0.1, -0.1);
        glVertex2f(-0.2, -0.1);
    glEnd();

    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POINTS);
        glVertex2f(0.0, -0.2);
        glVertex2f(0.1, -0.2);
        glVertex2f(0.2, -0.2);
        glVertex2f(-0.1, -0.2);
        glVertex2f(-0.2, -0.2);
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("Fish");
    glutDisplayFunc(render);

    glClearColor(1, 1, 1, 0.0);
    glutMainLoop();
    return 1;
}
