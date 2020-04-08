//
// Created by danseremet on 2020-04-07.
//

#ifndef OPENWORLD_COLORGENERATOR_H
#define OPENWORLD_COLORGENERATOR_H

#define GLEW_STATIC 1 // necessary for glew

#include <iostream>
#include <vector>
#include <map>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ColorGenerator {
private:
    float spread;
    float halfSpread;
    std::vector<glm::vec3> biomeColors;
    float part;

public:
    ColorGenerator(float spread);

    std::vector<std::vector<glm::vec3>> generateColors(std::vector<std::vector<float>> heights, float amplitude);

    glm::vec3 calculateColor(float height, float amplitude);
};


#endif //OPENWORLD_COLORGENERATOR_H
