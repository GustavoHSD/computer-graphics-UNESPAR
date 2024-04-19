#include <GL/freeglut_std.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <cstdlib>

struct Point {
    int x;
    int y;
};

struct Node {
    Point point;
    struct Node *next;
};

struct {
    struct Node *head;
} list;

int pointCount;

int mouseX = -1;
int mouseY = -1;
bool flag = false;

int windowHeight = 320;
int windowWidth = 320;

void mouseListener(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        switch (button) {
            case GLUT_LEFT_BUTTON: 
                mouseX = x;
                mouseY = glutGet(GLUT_WINDOW_HEIGHT) - y;
                flag = true;
                glutPostRedisplay();
                break;
            case GLUT_RIGHT_BUTTON: 
                // todo   
                break;
        }                    

    }
}

void addNewPoint(int x, int y) {
    Point point;
    point.x = x;
    point.y = y;

    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));   

    if (list.head == NULL) {
        list.head = newNode;
    } else {
        Node current = *list.head;
        while (current.next != NULL) {
            current = *current.next;
        }
        current.next = newNode;
    }
}

void render(void) {
    glColor3f(1, 1, 1);
    glPointSize(10);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));

    if (flag) {
        glBegin(GL_POINTS);
            glVertex2f((GLfloat)mouseX, (GLfloat)mouseY);
        glEnd();
        flag = false;
    }
    glFlush();
}

int main(int argc, char **argv) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutInitDisplayMode(GLUT_RGB | GLUT_RGBA);
    glutCreateWindow("Lines");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutDisplayFunc(render);
    glutMouseFunc(mouseListener);


    glutMainLoop();
    return 1;
}
