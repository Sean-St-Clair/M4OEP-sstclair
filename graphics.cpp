#include "graphics.h"
#include "cube.h"
#include "player.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

GLdouble width, height;
int wd;

// Game objects
vector<Cube> stars;
Player c;

void initStars() {
    int numStars = 200;
    double starX, starY;
    unsigned int size, brightness;
    Cube star;
    for (int i = 0; i < numStars; ++i) {
        starX = rand() % (int) (width * 1.5) - width;
        starY = rand() % (int) (height * 1.5) - height;
        size = rand() % 3;
        brightness = (rand() % 3) * (1 / 3);

        // Testing
//        starX = 100;
//        starY = 100;
//        size = 10;
//        brightness = 1;

        // Draw the star
        star = Cube({starX, starY, -600}, size);
        star.setFill(color(1, 1, 1, brightness));
        stars.push_back(star);
    }
}

void init() {
    srand(time(0));
    width = 1000;
    height = 700;
    initStars();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.0, 3.0, 6.0,  // eye position
              0.0, 0.0, 0.0,  // center position (not gaze direction)
              0.0, 1.0, 0.0); // up vector
}

void drawStars() {
    for (Cube star: stars) {
        star.draw(star.getFill(), false);
    }
}

void drawAxes() {
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-width / 2.0, 0.0, 0.0);
    glVertex3f(width / 2.0, 0.0, 0.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, height / 2.0, 0.0);
    glVertex3f(0.0, -height / 2.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, width);
    glVertex3f(0.0, 0.0, -width);
    glEnd();
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {

    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width / 2, width / 2, -height / 2, height / 2, -width, width);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glEnable(GL_DEPTH);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);

    // Draw here!
    drawStars();
    drawAxes();

    // Draw game entities
    c.draw(c.getFill(), true);

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    c.setMovingUp(false);
    c.setMovingDown(false);
    c.setMovingLeft(false);
    c.setMovingRight(false);

    switch (key) {
        case 'w':
            c.setMovingUp(true);
            break;
        case 's':
            c.setMovingDown(true);
            break;
        case 'a':
            c.setMovingLeft(true);
            break;
        case 'd':
            c.setMovingRight(true);
            break;
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {

    glutPostRedisplay();
}

void cursor(int x, int y) {

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        c.toggleInvincibility();
    }
    glutPostRedisplay();
}

void playerMovement() {
    double speed = 2.5;
    if (c.getMovingUp()) {
        c.move(0, 0, -speed * sqrt(2));
    }
    if (c.getMovingDown()) {
        c.move(0, 0, speed * sqrt(2));
    }
    if (c.getMovingLeft()) {
        c.move(-speed, 0, 0);
    }
    if (c.getMovingRight()) {
        c.move(speed, 0, 0);
    }

    // Keep player within bounds
    double xBounds = 400;
    double zBounds = 700;
    point center = c.getCenter();
    if (center.x > xBounds) {
        c.setCenter({xBounds, center.y, center.z});
    }
    if (center.x < -xBounds) {
        c.setCenter({-xBounds, center.y, center.z});
    }
    if (center.z > zBounds) {
        c.setCenter({center.x, center.y, zBounds});
    }
    if (center.z < -zBounds) {
        c.setCenter({center.x, center.y, -zBounds});
    }
}

void timer(int dummy) {
    playerMovement();
    glutPostRedisplay();
    glutTimerFunc(15, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv) {
    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int) width, (int) height);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2,
                           (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("3D Graphics!" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
