//
// Created by seans on 4/16/2023.
//

#include "celestial.h"

// Getters
double Celestial::getOrbitRadius() {
    return orbitRadius;
}

double Celestial::getOrbitSpeed() {
    return orbitSpeed;
}

double Celestial::getOrbitAdvancement() {
    return orbitAdvancement;
}

// Setters
void Celestial::setOrbitRadius(double r) {
    orbitRadius = r;
}

void Celestial::setOrbitSpeed(double r) {
    orbitSpeed = r;
}

void Celestial::setOrbitAdvancement(double r) {
    orbitAdvancement = r;
}

void Celestial::orbit() {
    orbitAdvancement += orbitSpeed;
    double orbitX = cos(orbitAdvancement) * orbitRadius;
    double orbitZ = sin(orbitAdvancement) * orbitRadius;
    setCenter({orbitX, 0, orbitZ});
}
