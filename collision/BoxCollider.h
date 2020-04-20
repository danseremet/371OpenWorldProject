//
// Created by jayohanna on 2020-04-19.
//

#ifndef OPENWORLD_BOXCOLLIDER_H
#define OPENWORLD_BOXCOLLIDER_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class BoxCollider {

public:

    GLfloat xMin;
    GLfloat xMax;
    GLfloat zMin;
    GLfloat zMax;
    GLfloat yMin;
    GLfloat yMax;

    BoxCollider(glm::vec3 scale, glm::vec3 translation);

    void initBox(glm::vec3 scale, glm::vec3 translation);

    void transformBox(glm::vec3 scale, glm::vec3 translation);
};


#endif //OPENWORLD_BOXCOLLIDER_H
