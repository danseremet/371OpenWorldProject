//
// Created by danseremet on 2020-04-04.
//

#include "Keyboard.h"

Keyboard::Keyboard() = default;

GLboolean Keyboard::monitorCounted = false;
bool Keyboard::oKeyReleased = true;

GLboolean Keyboard::randomTreeSeed = false;

void Keyboard::processInput(Game *game) {
    // Handle keyboard inputs

    GLFWwindow *window = game->getWindow();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    Camera *camera = game->getCamera();
    GLfloat dt = game->dt;


    int newWidth;
    int newHeight;
    glfwGetWindowSize(window, &newWidth, &newHeight);
    if ((newWidth - static_cast<int>(game->getScrWidth())) || (newHeight - static_cast<int>(game->getScrHeight()))) {
        game->setScrWidth(newWidth);
        game->setScrHeight(newHeight);
        game->updateAspectRatio();
        game->updateProjectionMatrix();
        glViewport(0, 0, newWidth, newHeight);
    }

    // On program launch set speed multiplier based on monitor count
    static constexpr float DEV_SLOW{1.0f};
    static constexpr float PROD_FAST{60.0f};
    constexpr int MONITOR_NUMBER_PROD{1};
    static float SPEED_MULTIPLIER{DEV_SLOW};
    if (!monitorCounted) {
        int count;
        glfwGetMonitors(&count);
        if (count == MONITOR_NUMBER_PROD) {
            SPEED_MULTIPLIER = PROD_FAST;
        }
    }

    float currentCameraSpeed = camera->cameraSpeed;

    // Camera logic from a lab (modified for separating panning/tilting/zooming)
    double mousePosX, mousePosY;
    glfwGetCursorPos(window, &mousePosX, &mousePosY);

    double dx = mousePosX - game->lastMousePosX;
    double dy = mousePosY - game->lastMousePosY;
    game->lastMousePosX = mousePosX;
    game->lastMousePosY = mousePosY;

    const float cameraAngularSpeed = SPEED_MULTIPLIER * 6.0f;

    glm::vec3 cameraSideVector = glm::cross(camera->cameraLookAt, glm::vec3(0.0f, 1.0f, 0.0f));



    // RIGHT MOUSE BUTTON PAN X
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        camera->cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;

        // Clamp vertical angle to [-85, 85] degrees
        if (camera->cameraHorizontalAngle > 360) {
            camera->cameraHorizontalAngle -= 360;
        } else if (camera->cameraHorizontalAngle < -360) {
            camera->cameraHorizontalAngle += 360;
        }

        float theta = glm::radians(camera->cameraHorizontalAngle);
        float phi = glm::radians(camera->cameraVerticalAngle);

        camera->cameraLookAt = glm::vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
        cameraSideVector = glm::cross(camera->cameraLookAt, glm::vec3(0.0f, 1.0f, 0.0f));

        glm::normalize(cameraSideVector);
    }

    // MIDDLE MOUSE BUTTON TILT Y
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
        camera->cameraVerticalAngle -= dy * cameraAngularSpeed * dt;

        // Clamp vertical angle to [-85, 85] degrees
        camera->cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, camera->cameraVerticalAngle));
        float theta = glm::radians(camera->cameraHorizontalAngle);
        float phi = glm::radians(camera->cameraVerticalAngle);

        camera->cameraLookAt = glm::vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
        cameraSideVector = glm::cross(camera->cameraLookAt, glm::vec3(0.0f, 1.0f, 0.0f));

        glm::normalize(cameraSideVector);
    }

    // LEFT MOUSE BUTTON ZOOM IN AND OUT of scene
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && dy > 0) {
        game->setFovy(game->getFovy() + 0.01f);
        game->updateProjectionMatrix();
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && dy < 0) {
        game->setFovy(game->getFovy() - 0.01f);
        game->updateProjectionMatrix();
    }

    // Extra camera movement keys (not a requirement, but easier to work with)
    if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS) { // forward W
        camera->cameraPosition += camera->cameraLookAt * dt * currentCameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS) { // backward S
        camera->cameraPosition -= camera->cameraLookAt * dt * currentCameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS) { // right D
        camera->cameraPosition += cameraSideVector * dt * currentCameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS) { // left A
        camera->cameraPosition -= cameraSideVector * dt * currentCameraSpeed;
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) { // R
        auto *tree = (TreeModel *) game->getTreeModel();
        tree->setTreeNumber();
    }

    // Return Home
    if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
        camera->initCamera();
        game->setFovy(70.0f);
        game->updateProjectionMatrix();
    }


    // Show Points
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        game->polygonMode = GL_POINT;
    }
    // Show Lines
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        game->polygonMode = GL_LINE;
    }
    // Show Triangles
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        game->polygonMode = GL_FILL;
    }

    // Refresh rock
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        if (oKeyReleased)
        {
            auto rocks = game->getRocks();

            std::map<int, std::map<int, Model*>>::iterator itr;
            std::map<int, Model*>::iterator ptr;

            for (itr = rocks.begin(); itr != rocks.end(); itr++) {
                for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
                    auto rock = (RockModel*) ptr->second;
                    rock->resetRock();
                }
            }
            oKeyReleased = false;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_RELEASE) {
        oKeyReleased = true;
    }
}
