//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_CAMERA_H
#define OPENWORLD_CAMERA_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
public:

    Camera();

    void initCamera();

    glm::mat4 getViewMatrix();
    glm::vec3 cameraPosition;
    glm::vec3 cameraLookAt;
    glm::vec3 cameraUp;

    // Other camera parameters
    GLfloat cameraSpeed;
    GLfloat cameraHorizontalAngle;
    GLfloat cameraVerticalAngle;
};


#endif //OPENWORLD_CAMERA_H
