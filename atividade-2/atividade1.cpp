#include <GL/freeglut_std.h>
#include <GL/glut.h>
#include <GL/gl.h>


int mouseX = -1;
int mouseY = -1;

void mouseListener(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON: 
            if (state == GLUT_DOWN) {
                mouseX = x;
                mouseY = glutGet(GLUT_WINDOW_HEIGHT) - y;
                glutPostRedisplay();
            }
            break;
        case GLUT_RIGHT_BUTTON: 
            // todo   
            break;
    }                    
        
}

void render(void) {
    glColor3f(1, 1, 1);
    glPointSize(10);
    if (mouseX != -1 && mouseY != -1) {
        glBegin(GL_POINTS);
            glVertex2f((GLfloat)mouseX / glutGet(GLUT_WINDOW_WIDTH), (GLfloat)mouseY / glutGet(GLUT_WINDOW_HEIGHT));
        glEnd();
    }

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(320, 320);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("Lines");
    glutDisplayFunc(render);
    glutMouseFunc(mouseListener);

    glutMainLoop();
    return 1;
}
