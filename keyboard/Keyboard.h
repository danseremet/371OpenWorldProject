//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_KEYBOARD_H
#define OPENWORLD_KEYBOARD_H



#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <algorithm>
#include "../game/Game.h"


class Keyboard {
public:
    Keyboard();

    static void processInput(Game* game);

private:
    static GLboolean monitorCounted;

    static GLboolean randomTreeSeed;
};


#endif //OPENWORLD_KEYBOARD_H
