


#ifndef OPENWORLD_BOXCOLLISION_H
#define OPENWORLD_BOXCOLLISION_H

#include <GL/glew.h>
#include <Mesh.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class BoxCollision {
public:

    explicit BoxCollision(Mesh* m, glm::mat4 transformation);

    std::vector <Vertex> returnVertices(Mesh* m);
    glm::mat4 returnTransformation();

 
};


#endif //OPENWORLD_MODEL_H