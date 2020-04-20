//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_MODEL_H
#define OPENWORLD_MODEL_H

#include <iostream>
#include <vector>
#include <utility>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../mesh/Mesh.h"
#include "../shader/Shader.h"
#include "../texture/Texture.h"
#include "../collision/BoxCollider.h"

// Abstract class
class Model {
public:

    explicit Model(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap);

    std::vector<Mesh*> meshes;
    std::vector<BoxCollider*> colliders;

    void draw();

    void loadModel();

    virtual void loadMeshes();

protected:
    std::map<std::string, Shader *> shadersMap;
    std::map<std::string, Texture *> texturesMap;
};


#endif //OPENWORLD_MODEL_H
