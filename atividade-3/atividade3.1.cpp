#include <GL/freeglut_std.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

struct Point {
    int x;
    int y;
};

struct Node {
    Point point;
    Node *next;
    Node *prev;
};

// initialize list
Node *head = NULL;
Node *tail = NULL;

// define window size
int windowHeight = 320;
int windowWidth = 320;

void addPoint(Point point) {
    Node *newNode = (Node*)malloc(sizeof(Node));    
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->point = point;

    if (head == NULL) {
        head = newNode; 
        tail = newNode; 
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode; 
    }
}

void openLastSaved() {
    free(head);
    ifstream file("data/atividade3.1.dat");
    Point point;
    while (file >> point.x >> point.y) { 
        addPoint(point);
    }
}

float euclidianDistance(int x1, int x2, int y1, int y2) {
    return sqrt(pow(double(x1 - x2), 2) + pow(double(y1 - y2), 2));
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

void displayList() {
    Node *current = head;
    printf("\n[");
    while (current != NULL) {
        printf("{ point.x: %d, point.y: %d }, ", current->point.x, current->point.y);
        current = current->next;
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
    // displayList();
    if (target == head) {
        head = head->next;
        head->prev = NULL;
    } else if (target == tail) {
        tail = tail->prev;
        tail->next = NULL;
    } else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }
    free(target);
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

void save() {
    ofstream file("data/atividade3.1.dat");
    Node *current = head;
    while (current != NULL) {
        file << current->point.x << " " << current->point.y << "\n";
        current = current->next;
    } 
    file.close();
}

void keyboardListener(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
            save();
            printf("drawing saved");
            break;
        case 'o':
            openLastSaved();
            glutPostRedisplay(); 
            break;
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
            break;
        } else {
            printf("point.x: %d, point.y: %d\t", current->point.x, current->point.y);
            printf("next.point.x: %d, next.point.y: %d\n", current->next->point.x, current->next->point.y);
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
    glutKeyboardFunc(keyboardListener);
    glutMainLoop();

    return 1;
}
