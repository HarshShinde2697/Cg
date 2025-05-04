#include <GL/freeglut.h>
#include <iostream>
using namespace std;

int radius;
int cx = 0, cy = 0; // Circle center

void plotPoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);
    glEnd();
}

void bresenhamCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    while (x <= y) {
        plotPoints(xc, yc, x, y);
        if (d <= 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0); // Red color

    // Draw circle in all quadrants
    bresenhamCircle(cx, cy, radius);
    bresenhamCircle(-cx, cy, radius);
    bresenhamCircle(cx, -cy, radius);
    bresenhamCircle(-cx, -cy, radius);

    glFlush();
}

void init() {
    gluOrtho2D(-400, 400, -400, 400);
    glClearColor(1, 1, 1, 1); // White background
}

int main(int argc, char** argv) {
    cout << "Enter radius of the circle: ";
    cin >> radius;
    cout << "Enter center x and y (positive values recommended): ";
    cin >> cx >> cy;

    glutInit(&argc, argv);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Bresenham Circle in All Quadrants");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
