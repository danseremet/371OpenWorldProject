//
// Created by danseremet on 2020-04-04.
//

#include "Camera.h"

Camera::Camera(glm::vec3 pos) {
    defaultPosition = pos;
    initCamera(pos);
}

glm::mat4 Camera::getViewMatrix() {
    // Set initial view matrix
    return lookAt(cameraPosition,  // eye
                  cameraPosition + cameraLookAt,  // center
                  cameraUp); // up

}

void Camera::initCamera(glm::vec3 pos) {
    cameraPosition = pos;
    cameraLookAt = glm::vec3(0.0f, -20.0f, -30.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // Other camera parameters
    cameraSpeed = 150.0f;
    cameraHorizontalAngle = 90.0f;
    cameraVerticalAngle = -20.0f;
}

const glm::vec3 &Camera::getDefaultPosition() const {
    return defaultPosition;
}
