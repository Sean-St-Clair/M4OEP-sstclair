#include "graphics.h"
#include "cube.h"
#include "player.h"
#include "celestial.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// Display variables
GLdouble width, height;
int wd;

// Game variables
vector<Cube> stars;
Player player;
Celestial sun;
vector<Celestial> planets;

// Timer variables
int invincibilityCountdown;

// Populates a vector with 200 stars with random placement, size, and luminosity
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

        // Add the star to vector
        star = Cube({starX, starY, -600}, size);
        star.setFill(color(1, 1, 1, brightness));
        star.setShadow(false);
        stars.push_back(star);
    }
}

// Initializes cubes which are to be rendered to the scene
void initGameObjects() {
    // Player
    player.setShadow(true);
    player.setCenter({0, 0, 450});
    player.resize(.7);

    // Sun
    sun.resize(1.7);
    sun.setFill(yellow);

    // Planets
    int numPlanets = 9;
    double orbitIncrement = 135;
    double orbitRadius;
    double orbitSpeed;
    Celestial planet;
    for (int i = 0; i < numPlanets; ++i) {
        orbitRadius = orbitIncrement * (i + 1) - (orbitIncrement / numPlanets * i);
        orbitSpeed = 1 / orbitRadius * 3;

        // Add the planet to vector
        planet = Celestial();
        planet.setFill(color(1, 1, 1));
        planet.setShadow(true);
        planet.setOrbitRadius(orbitRadius);
        planet.setOrbitSpeed(orbitSpeed);
        planet.setCenter({orbitRadius, 0, 0});
        planet.setOrbitAdvancement(rand() % 100);
        planets.push_back(planet);
    }
}

void init() {
    srand(time(0));
    width = 1000;
    height = 700;
    initStars();
    initGameObjects();
    // The player starts with 3 seconds of invincibility, as they become familiar with the planets.
    player.setInvincible(true);
    invincibilityCountdown = (60 * 3);
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

void drawAxes() {
    glLineWidth(1.0);
    glBegin(GL_LINES);
    glColor3f(.5, 0.5, 0.5);
//  glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-width, 0.0, 0.0);
    glVertex3f(width, 0.0, 0.0);
//  glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, height, 0.0);
    glVertex3f(0.0, -height, 0.0);
//  glColor3f(0.0, 0.0, 1.0);
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
    drawAxes();

    // Draw stars
    for (Cube star: stars) {
        star.draw(star.getFill());
    }

    // Draw game objects
    player.draw(player.getFill());
    sun.draw(sun.getFill());

    for (int i = 0; i < planets.size(); ++i) {
        planets[i].draw(planets[i].getFill());
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    player.setMovingUp(false);
    player.setMovingDown(false);
    player.setMovingLeft(false);
    player.setMovingRight(false);

    switch (key) {
        case 'w':
            player.setMovingUp(true);
            break;
        case 's':
            player.setMovingDown(true);
            break;
        case 'a':
            player.setMovingLeft(true);
            break;
        case 'd':
            player.setMovingRight(true);
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
    // Invincibility lasts for 2 seconds and takes 5 seconds to recharge
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && invincibilityCountdown <= -(60 * 5)) {
        player.setInvincible(true);
        invincibilityCountdown = (60 * 2);
    }
    glutPostRedisplay();
}

void playerMovement() {
    double speed = 2;
    if (player.getMovingUp()) {
        player.move(0, 0, -speed * sqrt(2));
    }
    if (player.getMovingDown()) {
        player.move(0, 0, speed * sqrt(2));
    }
    if (player.getMovingLeft()) {
        player.move(-speed, 0, 0);
    }
    if (player.getMovingRight()) {
        player.move(speed, 0, 0);
    }

    // Keep player within bounds
    double xBounds = 500;
    double zBounds = 900;
    point center = player.getCenter();
    if (center.x > xBounds) {
        player.setCenter({xBounds, center.y, center.z});
    }
    if (center.x < -xBounds) {
        player.setCenter({-xBounds, center.y, center.z});
    }
    if (center.z > zBounds) {
        player.setCenter({center.x, center.y, zBounds});
    }
    if (center.z < -zBounds) {
        player.setCenter({center.x, center.y, -zBounds});
    }
}

void checkCollisions() {
    // Player will not check further collisions if invincible
    if (player.getInvincible()) {
        return;
    }

    // Go through each planet and check collision
    for (int i = 0; i < planets.size(); ++i) {
        if (planets[i].isOverlapping(player)) {
            planets[i].setFill(color(1, 0, 0));
            player.setInvincible(true);
            invincibilityCountdown = (60 * 2);
            player.setLives(player.getLives() - 1);
            if (player.getLives() <= 0) {
                glutDestroyWindow(wd);
                exit(0);
            }
        } else {
            planets[i].setFill(defaultPlanet);
        }
    }
}

void timer(int dummy) {
    playerMovement();

    // Invincibility counts down 60 times per second
    if (invincibilityCountdown <= 0) {
        player.setInvincible(false);
    }
    --invincibilityCountdown;

    // Moves all the planets
    for (int i = 0; i < planets.size(); ++i) {
        planets[i].orbit();
    }

    // See if player is touching any planets
    checkCollisions();

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
    wd = glutCreateWindow("WIDDERSHINS (look it up)" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etplayer.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etplayer.
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
