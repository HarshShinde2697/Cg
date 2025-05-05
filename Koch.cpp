#include <GL/freeglut.h>
#include <cmath>

void drawKoch(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
        return;
    }

    float dx = (x2 - x1) / 3.0;
    float dy = (y2 - y1) / 3.0;

    float x3 = x1 + dx;
    float y3 = y1 + dy;

    float x5 = x2 - dx;
    float y5 = y2 - dy;

    float angle = M_PI / 3;
    float x4 = x3 + cos(angle) * (x5 - x3) - sin(angle) * (y5 - y3);
    float y4 = y3 + sin(angle) * (x5 - x3) + cos(angle) * (y5 - y3);

    drawKoch(x1, y1, x3, y3, depth - 1);
    drawKoch(x3, y3, x4, y4, depth - 1);
    drawKoch(x4, y4, x5, y5, depth - 1);
    drawKoch(x5, y5, x2, y2, depth - 1);
}

void display2() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);
    drawKoch(100, 300, 500, 300, 4);
    glFlush();
}
void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 640, 0, 480);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Fractal Pattern");

    init();
    glutDisplayFunc(display2);  // Change to display1 for Bezier Fractal
    glutMainLoop();
    return 0;
}
