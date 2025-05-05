#include <GL/freeglut.h>
#include <iostream>
using namespace std;

int fillMode = 0; // 1: flood fill, 2: boundary fill

void putPixel(int x, int y, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
        glVertex2i(x, y);
    glEnd();
    glFlush();
}

void getPixelColor(int x, int y, float* color) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color);
}

void floodFill(int x, int y, float* oldColor, float* newColor) {
    float color[3];
    getPixelColor(x, y, color);

    if (color[0] == oldColor[0] && color[1] == oldColor[1] && color[2] == oldColor[2]) {
        putPixel(x, y, newColor[0], newColor[1], newColor[2]);
        floodFill(x + 1, y, oldColor, newColor);
        floodFill(x - 1, y, oldColor, newColor);
        floodFill(x, y + 1, oldColor, newColor);
        floodFill(x, y - 1, oldColor, newColor);
    }
}

void boundaryFill(int x, int y, float* boundaryColor, float* fillColor) {
    float color[3];
    getPixelColor(x, y, color);

    if ((color[0] != boundaryColor[0] || color[1] != boundaryColor[1] || color[2] != boundaryColor[2]) &&
        (color[0] != fillColor[0] || color[1] != fillColor[1] || color[2] != fillColor[2])) {
        putPixel(x, y, fillColor[0], fillColor[1], fillColor[2]);
        boundaryFill(x + 1, y, boundaryColor, fillColor);
        boundaryFill(x - 1, y, boundaryColor, fillColor);
        boundaryFill(x, y + 1, boundaryColor, fillColor);
        boundaryFill(x, y - 1, boundaryColor, fillColor);
    }
}

void drawPolygon() {
    glColor3f(1, 0, 0); // red boundary
    glBegin(GL_LINE_LOOP);
        glVertex2i(200, 200);
        glVertex2i(300, 300);
        glVertex2i(400, 200);
        glVertex2i(300, 100);
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    y = 480 - y; // Convert y for OpenGL coordinates

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float oldColor[] = {1, 1, 1}; // white background
        float newColor[] = {0, 1, 0}; // green fill
        float boundaryColor[] = {1, 0, 0}; // red

        if (fillMode == 1) {
            floodFill(x, y, oldColor, newColor);
        } else if (fillMode == 2) {
            boundaryFill(x, y, boundaryColor, newColor);
        }
    }
}

void menu(int option) {
    fillMode = option;
}

void keyboard(unsigned char key, int, int) {
    if (key == 'r') {
        glClear(GL_COLOR_BUFFER_BIT);
        drawPolygon();
    }
}

void init() {
    glClearColor(1, 1, 1, 1); // white background
    gluOrtho2D(0, 640, 0, 480);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPolygon();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Flood Fill and Boundary Fill");
    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    // Right-click menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Flood Fill", 1);
    glutAddMenuEntry("Boundary Fill", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
