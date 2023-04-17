//
// Created by seans on 4/16/2023.
//

#include "cube.h"

#ifndef INC_3D_GRAPHICS_PLAYER_H
#define INC_3D_GRAPHICS_PLAYER_H

static color bodyColor = color(1, 1, 1);
static color invincibleColor = color(0, 1, 0);

class Player : public Cube {
private:
    color fill;
    bool movingUp, movingDown, movingLeft, movingRight;
public:
    // Constructors
    Player();

    // Getters
    color getFill();

    bool getMovingUp();

    bool getMovingDown();

    bool getMovingLeft();

    bool getMovingRight();

    // Setters
    void setFill(color c);

    void setMovingUp(bool moving);

    void setMovingDown(bool moving);

    void setMovingLeft(bool moving);

    void setMovingRight(bool moving);

    void toggleInvincibility();
};

#endif //INC_3D_GRAPHICS_PLAYER_H
