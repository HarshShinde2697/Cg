#include <GL/glut.h>
#include <cmath>

// Transformation Parameters
float scaleX = 1.0, scaleY = 1.0;
float rotationAngle = 0.0;
float reflectX = 1.0, reflectY = 1.0;
float pivotX = 0.0, pivotY = 0.0;

// Function to draw a simple triangle
void drawObject() {
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.0, 0.5);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(pivotX, pivotY, 0);
    glScalef(scaleX * reflectX, scaleY * reflectY, 1.0);
    glRotatef(rotationAngle, 0, 0, 1);
    glTranslatef(-pivotX, -pivotY, 0);

    drawObject();

    glutSwapBuffers();
}

// Keyboard function for transformations
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': scaleX += 0.2; scaleY += 0.2; break;  // Scale up
        case 'S': scaleX -= 0.2; scaleY -= 0.2; break;  // Scale down
        case 'r': rotationAngle += 10.0; break;         // Rotate clockwise
        case 'R': rotationAngle -= 10.0; break;         // Rotate counter-clockwise
        case 'x': reflectX *= -1; break;               // Reflect across X-axis
        case 'y': reflectY *= -1; break;               // Reflect across Y-axis
    }
    glutPostRedisplay();
}

// Initialization function
void init() {
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Transformations");
    
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    return 0;
}