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

struct Node {
    Point point;
    struct Node *next;
    struct Node *prev;
};

// initialize list
Node *head = NULL;
Node *tail = NULL;

// initialize point count and point buffer
int pointCount = 0;
Point pointBuffer;

// define window size
int windowHeight = 320;
int windowWidth = 320;



void addPoint(Point point) {
    struct Node *newNode = (Node*)malloc(sizeof(Node));    
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->point = point;

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
        
        pointCount++;
        pointBuffer = current->point;
        // printf("Point buffer { x: %d, y: %d}\n", pointBuffer.x, pointBuffer.y);
    }
}

float euclidianDistance(int x1, int x2, int y1, int y2) {
    return sqrt(pow(double(x1 - x2), 2) + pow(double(y1 - y2), 2));
}

void displayList() {
    Node *current = head;
    int click = 0;
    printf("\n[");
    while (current != NULL) {
        printf("{ point.x: %d, point.y: %d }, ", current->point.x, current->point.y);
        current = current->next;
        click++;
    }
    printf("]\n");
}

void removePoint(Point point) {
    if (head == NULL || head->next == NULL) {
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
    printf("target = { x: %d, y: %d }", target->point.x, target->point.y);
    displayList();
    if (target == head) {
        head = head->next;
        if (head != NULL) {
            head->prev = NULL;
        } else {
            tail = NULL; // If only one node, update tail
        }
        free(target); // Free memory of removed node
    } else if (target == tail) {
        tail = tail->prev;
        if (tail != NULL) {
            tail->next = NULL;
        } else {
            head = NULL; // If only one node, update head
        }
        free(target); // Free memory of removed node
    } else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
        free(target); // Free memory of removed node
    }
}


void displayListReversed() {
    Node *current = tail;
    int click = 0;
    printf("[");
    while (current != NULL) {
        printf("{ point.x: %d, point.y: %d }, ", current->point.x, current->point.y);
        current = current->prev;
        click++;
    }
    printf("]\n");
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
                removePoint(point);
                glutPostRedisplay();
                break;
        }
    }
}

void render(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    glPointSize(10);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT));
    
    Node *current = head;

    while (current != NULL) { 
        if (current->next == NULL) {
            glBegin(GL_POINTS);
                glVertex2f((GLfloat)current->point.x, (GLfloat)current->point.y);
            glEnd();
            break;
        } else {
            printf("point.x: %d, point.y: %d\t", current->point.x, current->point.y);
            printf("next.point.x: %d, next.point.y: %d\n", current->next->point.x, current->next->point.y);
            glBegin(GL_POINTS);
                glVertex2f((GLfloat)current->point.x, (GLfloat)current->point.y);
            glEnd();
            glBegin(GL_LINES);
                glVertex2f((GLfloat)current->point.x, (GLfloat)current->point.y);
                glVertex2f((GLfloat)current->next->point.x, (GLfloat)current->next->point.y);
            glEnd(); 
            current = current->next;
        }
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
    glutDisplayFunc(render);
    glutMouseFunc(mouseListener);
    glutMainLoop();

    return 1;
}
