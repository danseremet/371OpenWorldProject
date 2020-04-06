//
// Created by danseremet on 2020-04-04.
//

#include "Camera.h"

Camera::Camera() {
    initCamera();
}

glm::mat4 Camera::getViewMatrix() {
    // Set initial view matrix
    return lookAt(cameraPosition,  // eye
                  cameraPosition + cameraLookAt,  // center
                  cameraUp); // up

}

void Camera::initCamera() {
    cameraPosition = glm::vec3(0.0f, 20.0f, 10.0f);
    cameraLookAt = glm::vec3(0.0f, -20.0f, -30.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // Other camera parameters
    cameraSpeed = 15.0f;
    cameraHorizontalAngle = 90.0f;
    cameraVerticalAngle = -20.0f;
}
