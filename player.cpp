//
// Created by seans on 4/16/2023.
//

#include "player.h"

Player::Player() {
    setFill(bodyColor);
    lives = 3;
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

bool Player::getInvincible() {
    return invincible;
}

int Player::getLives() {
    return lives;
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

void Player::setInvincible(bool i) {
    invincible = i;
    if (invincible) {
        setFill(invincibleColor);
    } else {
        setFill(bodyColor);
    }
}

void Player::setLives(int l) {
    lives = l;
}