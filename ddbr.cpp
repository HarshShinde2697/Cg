#include <GL/freeglut.h>
#include <cmath>
#include <iostream>
using namespace std;

int lineType = 1; // 1: Simple, 2: Dotted, 3: Dashed, 4: Solid

void drawAxes() {
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    glVertex2i(-320, 0); glVertex2i(320, 0); // X-axis
    glVertex2i(0, -240); glVertex2i(0, 240); // Y-axis
    glEnd();
}

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// DDA Algorithm
void drawDDA(int xStart, int yStart, int xEnd, int yEnd, int type) {
    float dx = xEnd - xStart;
    float dy = yEnd - yStart;
    float steps = max(abs(dx), abs(dy));
    float xInc = dx / steps;
    float yInc = dy / steps;
    float x = xStart, y = yStart;

    for (int i = 0; i <= steps; i++) {
        bool draw = true;
        if (type == 2 && i % 4 != 0) draw = false;
        else if (type == 3 && (i / 5) % 2 == 1) draw = false;

        if (draw) plot(round(x), round(y));
        x += xInc;
        y += yInc;
    }
}

// Bresenham Algorithm
void drawBresenham(int xStart, int yStart, int xEnd, int yEnd, int type) {
    int dx = abs(xEnd - xStart);
    int dy = abs(yEnd - yStart);
    int x = xStart;
    int y = yStart;
    int sx = xEnd > xStart ? 1 : -1;
    int sy = yEnd > yStart ? 1 : -1;

    int err = dx - dy;
    int count = 0;

    while (true) {
        bool draw = true;
        if (type == 2 && count % 4 != 0) draw = false;
        else if (type == 3 && (count / 5) % 2 == 1) draw = false;

        if (draw) plot(x, y);
        if (x == xEnd && y == yEnd) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x += sx; }
        if (e2 < dx) { err += dx; y += sy; }
        count++;
    }
}

int xStart, yStart, xEnd, yEnd;
bool firstClick = true;

void mouse(int btn, int state, int x, int y) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int winX = x - 320;
        int winY = 240 - y;

        if (firstClick) {
            xStart = winX; yStart = winY;
            firstClick = false;
        } else {
            xEnd = winX; yEnd = winY;
            glColor3f(1, 0, 0);
            drawBresenham(xStart, yStart, xEnd, yEnd, lineType); // Change to drawDDA if needed
            glFlush();
            firstClick = true;
        }
    }
}

void menu(int option) {
    lineType = option;
    glutPostRedisplay();
}

void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(-320, 320, -240, 240);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Line Drawing with DDA and Bresenham");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    // Right-click menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Simple Line", 1);
    glutAddMenuEntry("Dotted Line", 2);
    glutAddMenuEntry("Dashed Line", 3);
    glutAddMenuEntry("Solid Line", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
