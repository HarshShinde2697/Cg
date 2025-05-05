#include <GL/freeglut.h>
#include <vector>
#include <iostream>

using namespace std;

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

int xmin = 100, ymin = 100, xmax = 300, ymax = 300;

struct Point {
    int x, y;
    Point(int a, int b) : x(a), y(b) {}
};

vector<Point> polygon;
bool clipped = false;

int computeCode(int x, int y) {
    int code = INSIDE;
    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;
    if (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;
    return code;
}

bool cohenSutherlandClip(int &x1, int &y1, int &x2, int &y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    while (true) {
        if ((code1 | code2) == 0) {
            accept = true;
            break;
        } else if ((code1 & code2) != 0) {
            break;
        } else {
            int codeOut = code1 ? code1 : code2;
            int x, y;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
                y = ymax;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
                y = ymin;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
                x = xmax;
            } else {
                y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    return accept;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Clipping window
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(xmin, ymin);
        glVertex2i(xmax, ymin);
        glVertex2i(xmax, ymax);
        glVertex2i(xmin, ymax);
    glEnd();

    // Original polygon
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < polygon.size(); ++i) {
        glVertex2i(polygon[i].x, polygon[i].y);
    }
    glEnd();

    // Clipped polygon
    if (clipped && polygon.size() > 1) {
        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
        for (int i = 0; i < polygon.size(); ++i) {
            int j = (i + 1) % polygon.size();
            int x1 = polygon[i].x, y1 = polygon[i].y;
            int x2 = polygon[j].x, y2 = polygon[j].y;
            if (cohenSutherlandClip(x1, y1, x2, y2)) {
                glVertex2i(x1, y1);
                glVertex2i(x2, y2);
            }
        }
        glEnd();
    }

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = 500 - y;
        polygon.push_back(Point(x, y));
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'c':
            clipped = true;
            break;
        case 'r':
            polygon.clear();
            clipped = false;
            break;
        case 'q':
            exit(0);
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cohen-Sutherland Polygon Clipping");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
