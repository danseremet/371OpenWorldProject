//
// Created by jayohanna on 2020-04-19.
//

#include "BoxCollider.h"

BoxCollider::BoxCollider(glm::vec3 scale, glm::vec3 translation) {
    initBox(scale, translation);
    transformBox(scale, translation);
}

void BoxCollider::initBox(glm::vec3 scale, glm::vec3 translation) {
    xMin = -0.5f;
    xMax = 0.5f;
    zMin = -0.5f;
    zMax = 0.5f;
    yMin = -0.5f;
    yMax = 0.5f;
}

void BoxCollider::transformBox(glm::vec3 scale, glm::vec3 translation) {
    xMin *= scale[0];
    xMax *= scale[0];
    zMin *= scale[2];
    zMax *= scale[2];
    yMin *= scale[1];
    yMax *= scale[1];
    
    xMin += translation[0];
    xMax += translation[0];
    zMin += translation[2];
    zMax += translation[2];
    yMin += translation[1];
    yMax += translation[1];
}