//
// Created by danseremet on 2020-04-04.
//

#include "WindowManager.h"

GLFWwindow* WindowManager::window = nullptr;

WindowManager::WindowManager() {
    // private constructor
}


void WindowManager::createWindow() {
    // Initialize GLFW and OpenGL version
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create Window and rendering context using GLFW
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Comp371 - Assignment 2", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        throw WindowException();
    }
    glfwMakeContextCurrent(window);

    // Disable cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        throw WindowException();
    }

    //  background
    glClearColor(0.2f, 0.4f, 0.9f, 1.0f);
//    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

GLFWwindow *WindowManager::getWindow() {
    if (window == nullptr) {
        createWindow();
    }
    return window;
}



WindowManager::~WindowManager() {
    glfwDestroyWindow(window);
}

GLuint WindowManager::getDefaultScreenWidth() {
    return SCR_WIDTH;
}

GLuint WindowManager::getDefaultScreenHeight() {
    return SCR_HEIGHT;
}