#include <GL/freeglut.h>
#include <cmath>

// Ball properties
float ballX = 50.0f;
float ballY = 50.0f;
float velocityY = 2.0f;
float gravity = -0.1f;
float radius = 20.0f;

bool goingUp = true;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw ball
    glColor3f(1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(ballX, ballY);
    for (int i = 0; i <= 100; i++) {
        float angle = i * 2.0f * 3.1416f / 100;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(ballX + x, ballY + y);
    }
    glEnd();

    glFlush();
}

void timer(int) {
    // Update physics
    ballY += velocityY;
    velocityY += gravity;

    // Bounce effect
    if (ballY <= radius) {
        ballY = radius;
        velocityY = 2.0f; // bounce up
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // roughly 60 FPS
}

void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 640, 0, 480);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bouncing Ball Animation - CG Principles");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
