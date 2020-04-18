//
// Created by jayohanna on 2020-04-15.
//

#include "Player.h"

Player::Player(glm::vec3 pos) {
    defaultPosition = pos;
    initPlayer(pos);
}

void Player::initPlayer(glm::vec3 pos) {
    x = pos[0];
    y = pos[1];
    z = pos[2];

    // Other camera parameters
    playerSpeed = 15.0f;
    jumpSpeed = 30.0f;
    height = 2.0f;
    verticalVelocity = 0.0f;
}

void Player::movePlayer(GLfloat x, GLfloat y, GLfloat z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

const glm::vec3& Player::getDefaultPosition() const {
    return defaultPosition;
}
