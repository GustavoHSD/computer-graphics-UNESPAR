#include <GL/freeglut.h>
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <math.h>
#include <thread>
#include <chrono>
#include <vector>

#define num_segments 50

using namespace std;

class Point {
public:
    float x;
    float y;
    Point() : x(0), y(0) {}
    Point(float x, float y) : x(x), y(y) {}
};

class Petal {
    Point center;
    Point points[num_segments];
    float radius;
    float flowerRadius;
public:
    Petal() : center(Point(0, 0)), radius(20), flowerRadius(0) {}
    Petal(Point center, float radius, float flowerRadius) : center(center), radius(radius), flowerRadius(flowerRadius) {
        this->center = center;
        this->radius = radius;
        this->flowerRadius = flowerRadius;

        for (int i = 0; i < num_segments; i++) {
            float theta = M_PI * float(i) / float(num_segments);
            float x = -this->radius * cos(theta);
            float y = this->radius * sin(theta)+flowerRadius;
            this->points[i] = Point(x + center.x, y + center.y);
        }
    }

    Point getPoint(int index) {
        return this->points[index];
    }

    void setPoint(int index, Point point) {
        this->points[index] = point;
    }

    void draw() {
        glBegin(GL_LINE_STRIP);
        glVertex2f(this->center.x, this->center.y);
        for (int i = 0; i < num_segments; ++i) {
            glVertex2f(this->points[i].x, this->points[i].y);
        }
        glVertex2f(this->center.x, this->center.y);
        glEnd();
    }

    void rotateAround(Point pivot, float angle) {
        float s = sinf(angle);
        float c = cosf(angle);
        for (int i = 0; i < num_segments; ++i) {
            float x_new = pivot.x + (points[i].x - pivot.x) * c - (points[i].y - pivot.y) * s;
            float y_new = pivot.y + (points[i].x - pivot.x) * s + (points[i].y - pivot.y) * c;
            points[i].x = x_new;
            points[i].y = y_new;
        }
    }
};

class Flower {
    Petal petals[8];
    Point center;
    float radius;
    float rotationAngle;
public:
    Flower(Point center, float radius) : center(center), radius(radius), rotationAngle(0.0f){
        float angle = M_PI * 2 / 8;
        float petalRadius = radius * sqrt(2 - sqrt(2)) / 2;
        for(int i = 0; i < 8; i++) {
            Petal petal(this->center, petalRadius, this->radius);
            petal.rotateAround(center, angle * i);
            this->petals[i] = petal; 
        }
    }

    void draw() {
        for(Petal petal : petals) {
            petal.draw();
        }
    } 

    void spin(float angle) {
        rotationAngle += angle;
        float anglePerPetal = M_PI * 2 / 8;
        for(int i = 0; i < 8; i++) {
            petals[i].rotateAround(center, anglePerPetal * i + rotationAngle);
        }
    }
};

static Point click(320, 240);
static vector<Flower> flowers;

void render(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    for (Flower f : flowers) {
        f.draw(); 
    }
    glFlush();
}

void mouseListener(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        click = Point(x, y);
        flowers.push_back(Flower(click, 200));
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

void idle() {
    if (flowers.size() > 0) {
        flowers.back().spin(0.000001f);
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set clear color to black
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Flower");
    init();

    glutDisplayFunc(render);
    glutMouseFunc(mouseListener);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}

