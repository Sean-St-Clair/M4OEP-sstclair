//
// Created by seans on 4/16/2023.
//

#ifndef INC_3D_GRAPHICS_CELESTIAL_H
#define INC_3D_GRAPHICS_CELESTIAL_H

#include "cube.h"

static color yellow = color(1, 1, 0, 1);

class Celestial : public Cube {
private:
public:
    void orbit();
};

#endif //INC_3D_GRAPHICS_CELESTIAL_H
