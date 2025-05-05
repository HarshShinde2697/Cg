#include <GL/freeglut.h>
#include <cmath>

void drawBezier(float x0, float y0, float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        glBegin(GL_LINE_STRIP);
        for (float t = 0.0; t <= 1.0; t += 0.01) {
            float xt = (1 - t) * (1 - t) * x0 + 2 * (1 - t) * t * x1 + t * t * x2;
            float yt = (1 - t) * (1 - t) * y0 + 2 * (1 - t) * t * y1 + t * t * y2;
            glVertex2f(xt, yt);
        }
        glEnd();
    } else {
        float mx1 = (x0 + x1) / 2;
        float my1 = (y0 + y1) / 2;
        float mx2 = (x1 + x2) / 2;
        float my2 = (y1 + y2) / 2;
        float mx = (mx1 + mx2) / 2;
        float my = (my1 + my2) / 2;
        drawBezier(x0, y0, mx1, my1, mx, my, depth - 1);
        drawBezier(mx, my, mx2, my2, x2, y2, depth - 1);
    }
}

void display1() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.1f, 0.6f, 0.1f);
    drawBezier(100, 100, 250, 300, 400, 100, 4);
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
    glutDisplayFunc(display1);  // Change to display1 for Bezier Fractal
    glutMainLoop();
    return 0;
}
