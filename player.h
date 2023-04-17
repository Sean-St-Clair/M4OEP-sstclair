//
// Created by seans on 4/16/2023.
//

#include "cube.h"

#ifndef INC_3D_GRAPHICS_PLAYER_H
#define INC_3D_GRAPHICS_PLAYER_H

static color bodyColor = color(0, 1, 0);
static color invincibleColor = color(1, .5, .5);

class Player : public Cube {
private:
    bool movingUp, movingDown, movingLeft, movingRight;
    bool invincible;
    int lives;
public:
    // Constructors
    Player();

    // Getters
    bool getMovingUp();

    bool getMovingDown();

    bool getMovingLeft();

    bool getMovingRight();

    bool getInvincible();

    int getLives();

    // Setters
    void setMovingUp(bool moving);

    void setMovingDown(bool moving);

    void setMovingLeft(bool moving);

    void setMovingRight(bool moving);

    void setInvincible(bool invincible);

    void setLives(int lives);
};

#endif //INC_3D_GRAPHICS_PLAYER_H
