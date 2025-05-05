#include <GL/freeglut.h>
#include <iostream>
#include <string>
using namespace std;

// Clipping window and line coordinates
int X1, Y1, X2, Y2;
float x1, y1, x2, y2;
bool showClipped = false; // Switch between before/after clipping

// Utility to draw text at a position
void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void init() {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    glClearColor(1, 1, 1, 1); // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping rectangle
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(X1, Y1);
        glVertex2i(X2, Y1);
        glVertex2i(X2, Y2);
        glVertex2i(X1, Y2);
    glEnd();

    if (!showClipped) {
        // BEFORE Clipping: draw original line
        glColor3f(0, 0, 1); // Blue
        glBegin(GL_LINES);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        glEnd();
        drawText(20, 450, "Before Clipping");
    } else {
        // AFTER Clipping
        drawText(20, 450, "After Clipping");

        float cx1 = x1, cy1 = y1, cx2 = x2, cy2 = y2;
        int op[2][4];
        op[0][3] = (x1 < X1);  op[0][2] = (x1 > X2);
        op[0][0] = (y1 < Y1);  op[0][1] = (y1 > Y2);
        op[1][3] = (x2 < X1);  op[1][2] = (x2 > X2);
        op[1][0] = (y2 < Y1);  op[1][1] = (y2 > Y2);

        float m = (x2 - x1 != 0) ? (y2 - y1) / (x2 - x1) : 0;

        if (!((op[0][0] && op[1][0]) || (op[0][1] && op[1][1]) ||
              (op[0][2] && op[1][2]) || (op[0][3] && op[1][3]))) {

            if (op[0][0]) { cx1 = x1 + (Y1 - y1) / m; cy1 = Y1; }
            if (op[0][1]) { cx1 = x1 + (Y2 - y1) / m; cy1 = Y2; }
            if (op[0][2]) { cy1 = y1 + m * (X2 - x1); cx1 = X2; }
            if (op[0][3]) { cy1 = y1 + m * (X1 - x1); cx1 = X1; }

            if (op[1][3]) { cy2 = y2 + m * (X1 - x2); cx2 = X1; }
            if (op[1][2]) { cy2 = y2 + m * (X2 - x2); cx2 = X2; }
            if (op[1][0]) { cx2 = x2 + (Y1 - y2) / m; cy2 = Y1; }
            if (op[1][1]) { cx2 = x2 + (Y2 - y2) / m; cy2 = Y2; }

            glColor3f(1, 0, 0); // Red
            glBegin(GL_LINES);
                glVertex2f(cx1, cy1);
                glVertex2f(cx2, cy2);
            glEnd();
        }
    }

    glFlush();
}

// Timer callback to switch to clipped view
void timer(int) {
    showClipped = true;
    glutPostRedisplay(); // Redraw the window
}

int main(int argc, char** argv) {
    cout << "Enter Clipping Window (X1 Y1 X2 Y2): ";
    cin >> X1 >> Y1 >> X2 >> Y2;
    cout << "Enter Line (x1 y1 x2 y2): ";
    cin >> x1 >> y1 >> x2 >> y2;

    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);

    // Call timer after 3000 milliseconds (3 seconds)
    glutTimerFunc(3000, timer, 0);

    glutMainLoop();
    return 0;
}
