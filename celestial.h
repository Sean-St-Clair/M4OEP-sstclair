//
// Created by seans on 4/16/2023.
//

#ifndef INC_3D_GRAPHICS_CELESTIAL_H
#define INC_3D_GRAPHICS_CELESTIAL_H

#include "cube.h"
#include <cmath>

static color yellow = color(1, 1, 0, 1);
static color defaultPlanet = color(1, 1, 1, 1);
static color prizeColor = color(0, 1, 1, 1);

class Celestial : public Cube {
private:
    double orbitRadius, orbitSpeed, orbitAdvancement;
public:
    // Getters
    double getOrbitRadius();

    double getOrbitSpeed();

    double getOrbitAdvancement();

    // Setters
    void setOrbitRadius(double r);

    void setOrbitSpeed(double r);

    void setOrbitAdvancement(double r);

    // TODO: comments
    void orbit();
};

#endif //INC_3D_GRAPHICS_CELESTIAL_H
