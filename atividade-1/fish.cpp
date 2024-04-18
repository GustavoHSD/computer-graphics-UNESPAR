#include <GL/glut.h>
#include <GL/gl.h>

void render(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.5, 0.5, 0.5);

    // first triangle (body)
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0, 0.5);
        glVertex2f(0.0, -0.5);
        glVertex2f(0.5, 0.0);
    glEnd();

    // second triangle (body)
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0, 0.5);
        glVertex2f(0.0, -0.5);
        glVertex2f(-0.5, 0.0);
    glEnd();

    // third triangle (tail)
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.2, 0.0);
        glVertex2f(-0.7, 0.5);
        glVertex2f(-0.7, -0.5);
    glEnd();

    // eye
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
        glVertex2f(0.2, 0.2);
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(320, 320);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("Fish");
    glutDisplayFunc(render);

    glClearColor(0, 0, 0.5, 0.0);
    glutMainLoop();
    return 1;
}
