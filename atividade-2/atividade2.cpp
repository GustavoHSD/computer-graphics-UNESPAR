#include <GL/freeglut_std.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>

struct Point {
    int x;
    int y;
};

Point initPoint() {
    Point point;
    point.x = 0;
    point.y = 0;
    return point;
}
struct Node {
    Point point;
    struct Node *next;
    struct Node *prev;
};

// initialize list
Node *head = NULL;
Node *tail = NULL;

// initialize active point
Node *activeNode = NULL;

int windowHeight = 320;
int windowWidth = 320;

float euclidianDistance(int x1, int x2, int y1, int y2) {
    return sqrt(pow(double(x1 - x2), 2) + pow(double(y1 - y2), 2));
}

void addPoint(Point point) {
    struct Node *newNode = (Node*)malloc(sizeof(Node));    
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->point = point;
    activeNode = newNode;

    if (head == NULL) {
        head = (Node *) malloc(sizeof(Node));
        head->point = point;
        head->next = NULL;
        head->prev = NULL;

        tail = (Node *) malloc(sizeof(Node));
        tail->point = point;
        tail->next = NULL;
        tail->prev = NULL;
    } else {
        Node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = (Node *) malloc(sizeof(Node));
        current->next = newNode;
        newNode->prev = (Node *) malloc(sizeof(Node));
        newNode->prev = current;
        tail = newNode; 
    }
}

void changeActivePoint(Point point) {
    if (head == NULL) {
        return;
    }
    float distance = euclidianDistance(head->point.x, point.x, head->point.y, point.y);
    Node *target = head;
    Node *current = head;

    while (current != NULL) {
        float currentDistance = euclidianDistance(current->point.x, point.x, current->point.y, point.y);
        if (currentDistance < distance) {
            distance = currentDistance;
            target = current;
        }
        current = current->next; 
    }
    // printf("target = { x: %d, y: %d }", target->point.x, target->point.y);
    // displayList();
    activeNode = target;
}


void mouseListener(int button, int state, int x, int y) {
if (state == GLUT_DOWN) {
        Point point;
        point.x = x;
        point.y = glutGet(GLUT_WINDOW_HEIGHT) - y;
        switch (button) {
            case GLUT_LEFT_BUTTON: 
                printf("\nLeft click\n");
                addPoint(point); 
                glutPostRedisplay();
                break;
            case GLUT_RIGHT_BUTTON: 
                printf("\nRight click\n");
                changeActivePoint(point);
                glutPostRedisplay();
                break;
        }
    }
}

void specialKeyListener(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            // printf("GLUT_KEY_UP\n");
            activeNode->point.y += 10;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            // printf("GLUT_KEY_DOWN\n");
            activeNode->point.y -= 10;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            // printf("GLUT_KEY_RIGHT\n");
            activeNode->point.x += 10;
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            // printf("GLUT_KEY_LEFT\n");
            activeNode->point.x -= 10;
            glutPostRedisplay();
            break;
    }
}

void keyListener(unsigned char key, int x, int y) {
    // printf("key: { %c, %d }\n", key, key);
    switch (key) {
        case 119:
            // printf("GLUT_KEY_UP\n");
            activeNode->point.y += 10;
            glutPostRedisplay();
            break;
        case 115:
            // printf("GLUT_KEY_DOWN\n");
            activeNode->point.y -= 10;
            glutPostRedisplay();
            break;
        case 100:
            // printf("GLUT_KEY_RIGHT\n");
            activeNode->point.x += 10;
            glutPostRedisplay();
            break;
        case 97:
            // printf("GLUT_KEY_LEFT\n");
            activeNode->point.x -= 10;
            glutPostRedisplay();
            break;
    }
}

void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glPointSize(10);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));
    
    Node *current = head;

    while(current != NULL) {
        glBegin(GL_POINTS);
            glVertex2f((GLfloat)current->point.x, (GLfloat)current->point.y);
        glEnd();
        current = current->next;
    }
 
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutInitDisplayMode(GLUT_RGB | GLUT_RGBA);

    glutCreateWindow("Lines");
    glutDisplayFunc(render);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // listeners
    glutMouseFunc(mouseListener);
    glutSpecialFunc(specialKeyListener);
    glutKeyboardFunc(keyListener);

    glutMainLoop();

    return 1;
}
