//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_WINDOWMANAGER_H
#define OPENWORLD_WINDOWMANAGER_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "WindowException.h"

#include <iostream>


class WindowManager {
public:
    ~WindowManager();

    static GLFWwindow *getWindow();
    static GLuint getDefaultScreenWidth();
    static GLuint getDefaultScreenHeight();

//    static Camera *camera;
    static GLFWwindow *window;

private:
    static void createWindow();
    // settings
    static const GLuint SCR_WIDTH = 1024;
    static const GLuint SCR_HEIGHT = 768;

    WindowManager();
};



#endif //OPENWORLD_WINDOWMANAGER_H
