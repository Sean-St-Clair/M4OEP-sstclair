//
// Created by seans on 4/16/2023.
//

#include "player.h"

Player::Player() {
    setFill(bodyColor);
}

bool Player::getMovingUp() {
    return movingUp;
}

bool Player::getMovingDown() {
    return movingDown;
}

bool Player::getMovingLeft() {
    return movingLeft;
}

bool Player::getMovingRight() {
    return movingRight;
}

void Player::setMovingUp(bool moving) {
    movingUp = moving;
}

void Player::setMovingDown(bool moving) {
    movingDown = moving;
}

void Player::setMovingLeft(bool moving) {
    movingLeft = moving;
}

void Player::setMovingRight(bool moving) {
    movingRight = moving;
}

void Player::toggleInvincibility() {
    if (getFill() == bodyColor) {
        setFill(invincibleColor);
    } else {
        setFill(bodyColor);
    }
}