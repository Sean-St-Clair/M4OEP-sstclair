#include <math.h>
#include "cube.h"
#include "graphics.h"

/********************* Color Struct ********************/

color::color() : red(0.0), green(0.0), blue(0.0), alpha(1.0) {
}

color::color(double r, double g, double b, double a) : red(r), green(g), blue(b), alpha(a) {
}

color::color(double r, double g, double b) : red(r), green(g), blue(b), alpha(1.0) {
}

/****************** Private helper methods *******************/
void Cube::resetCorners() {
    corners.clear();
    corners.resize(8);
    corners[0] = {center.x + (edge_length / 2.0), center.y + (edge_length / 2.0), center.z + (edge_length / 2.0)};
    corners[1] = {center.x - (edge_length / 2.0), center.y + (edge_length / 2.0), center.z + (edge_length / 2.0)};
    corners[2] = {center.x + (edge_length / 2.0), center.y - (edge_length / 2.0), center.z + (edge_length / 2.0)};
    corners[3] = {center.x - (edge_length / 2.0), center.y - (edge_length / 2.0), center.z + (edge_length / 2.0)};
    corners[4] = {center.x + (edge_length / 2.0), center.y + (edge_length / 2.0), center.z - (edge_length / 2.0)};
    corners[5] = {center.x - (edge_length / 2.0), center.y + (edge_length / 2.0), center.z - (edge_length / 2.0)};
    corners[6] = {center.x + (edge_length / 2.0), center.y - (edge_length / 2.0), center.z - (edge_length / 2.0)};
    corners[7] = {center.x - (edge_length / 2.0), center.y - (edge_length / 2.0), center.z - (edge_length / 2.0)};
}

void Cube::drawPoint(const point &p) const {
    glVertex3f(p.x, p.y, p.z);
}

void Cube::updateCorners(double deltaX, double deltaY, double deltaZ) {
    for (point &p: corners) {
        p.x += deltaX;
        p.y += deltaY;
        p.z += deltaZ;
    }
}

/********************** Public methods *************************/
Cube::Cube() {
    center = {0, 0, 0};
    edge_length = 50;
    resetCorners();
}

Cube::Cube(point center, unsigned int edge_length) {
    this->center = center;
    this->edge_length = edge_length;
    resetCorners();
}

color Cube::getFill() {
    return fill;
}

point Cube::getCenter() {
    return center;
}

bool Cube::getShadow() {
    return shadow;
}

void Cube::setFill(color c) {
    fill = c;
}

void Cube::setCenter(point p) {
    double oldCenterX = center.x, oldCenterY = center.y, oldCenterZ = center.z;
    center = p;
    double deltaX = center.x - oldCenterX;
    double deltaY = center.y - oldCenterY;
    double deltaZ = center.z - oldCenterZ;
    updateCorners(deltaX, deltaY, deltaZ);
}

void Cube::setShadow(bool s) {
    shadow = s;
}

void Cube::draw() const {
    glBegin(GL_QUADS);

    // Yellow
    glColor3f(1, 1, 0);
    drawPoint(corners[0]);
    drawPoint(corners[1]);
    drawPoint(corners[3]);
    drawPoint(corners[2]);

    // Magenta
    glColor3f(1, 0, 1);
    drawPoint(corners[5]);
    drawPoint(corners[4]);
    drawPoint(corners[6]);
    drawPoint(corners[7]);

    // Cyan
    glColor3f(0, 1, 1);
    drawPoint(corners[4]);
    drawPoint(corners[0]);
    drawPoint(corners[2]);
    drawPoint(corners[6]);

    // White
    glColor3f(1, 1, 1);
    drawPoint(corners[1]);
    drawPoint(corners[5]);
    drawPoint(corners[7]);
    drawPoint(corners[3]);

    // Gray
    glColor3f(.5, .5, .5);
    drawPoint(corners[4]);
    drawPoint(corners[5]);
    drawPoint(corners[1]);
    drawPoint(corners[0]);

    // Purple
    glColor3f(.5, 0, 1);
    drawPoint(corners[2]);
    drawPoint(corners[3]);
    drawPoint(corners[7]);
    drawPoint(corners[6]);

    glEnd();
}

void Cube::draw(color c) const {
    glBegin(GL_QUADS);
    // Modify the color in accordance with the z value to help signify depth
    double range = 1000;
    double depth = (range - abs(center.z)) / range;
    double max = 1;
    double min = .05;
    if (depth > max) {
        depth = max;
    }
    if (depth < min) {
        depth = min;
    }
    color m = color(c.red * depth, c.green * depth, c.blue * depth, c.alpha);

    // Regular color
    glColor4f(c.red, c.green, c.blue, c.alpha);
    if (shadow) {
        glColor4f(m.red, m.green, m.blue, m.alpha);
    }
    drawPoint(corners[0]);
    drawPoint(corners[1]);
    drawPoint(corners[3]);
    drawPoint(corners[2]);

    drawPoint(corners[5]);
    drawPoint(corners[4]);
    drawPoint(corners[6]);
    drawPoint(corners[7]);

    // Darkest version of color
    if (shadow) {
        glColor4f(m.red * .5, m.green * .5, m.blue * .5, m.alpha);
    }
    drawPoint(corners[4]);
    drawPoint(corners[0]);
    drawPoint(corners[2]);
    drawPoint(corners[6]);

    drawPoint(corners[1]);
    drawPoint(corners[5]);
    drawPoint(corners[7]);
    drawPoint(corners[3]);

    // Slightly darker color
    if (shadow) {
        glColor4f(m.red * .75, m.green * .75, m.blue * .75, m.alpha);
    }
    drawPoint(corners[4]);
    drawPoint(corners[5]);
    drawPoint(corners[1]);
    drawPoint(corners[0]);

    drawPoint(corners[2]);
    drawPoint(corners[3]);
    drawPoint(corners[7]);
    drawPoint(corners[6]);

    glEnd();
}

void Cube::rotate(double theta_x, double theta_y, double theta_z) {
    double old_x = 0, old_y = 0, old_z = 0;
    double center_x = center.x, center_y = center.y, center_z = center.z;
    // Move to origin
    move(-center_x, -center_y, -center_z);
    // Rotate x
    for (point &p: corners) {
        old_y = p.y;
        old_z = p.z;
        p.y = old_y * cos(theta_x) - old_z * sin(theta_x);
        p.z = old_y * sin(theta_x) + old_z * cos(theta_x);
    }
    // Rotate y
    for (point &p: corners) {
        old_x = p.x;
        old_z = p.z;
        p.x = old_x * cos(theta_y) - old_z * sin(theta_y);
        p.z = old_x * sin(theta_y) + old_z * cos(theta_y);
    }
    // Rotate z
    for (point &p: corners) {
        old_y = p.y;
        old_x = p.x;
        p.y = old_y * cos(theta_z) - old_x * sin(theta_z);
        p.x = old_y * sin(theta_z) + old_x * cos(theta_z);
    }
    // Move back to position
    move(center_x, center_y, center_z);
}

void Cube::move(double deltaX, double deltaY, double deltaZ) {
    // Move x, y, and z coordinates by their respective deltas, then update corners.
    center.x += deltaX;
    center.y += deltaY;
    center.z += deltaZ;
    updateCorners(deltaX, deltaY, deltaZ);
}

void Cube::resize(bool grow) {
    // Scale factor is larger if grow is true, smaller otherwise
    double scaleFactor = grow ? 1.1 : 0.9;
    double center_x = center.x, center_y = center.y, center_z = center.z;
    // Move to origin
    move(-center_x, -center_y, -center_z);
    // Scale each corner vector by new scaleFactor
    for (point &p: corners) {
        p.x *= scaleFactor;
        p.y *= scaleFactor;
        p.z *= scaleFactor;
    }
    // Move back to position
    move(center_x, center_y, center_z);
}