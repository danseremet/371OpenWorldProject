//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_MESH_H
#define OPENWORLD_MESH_H

#define GLEW_STATIC 1 // necessary for glew

#include <iostream>
#include <vector>
#include <map>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/normal.hpp>
#include "../shader/Shader.h"
#include "../texture/Texture.h"
#include "../collision/BoxCollider.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec3 Normal;
};

class Mesh {
public:
    explicit Mesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap);

    virtual void draw();

    void loadMesh();

    BoxCollider* getCollider();

protected:
    std::vector<Vertex> vertices;

    GLuint VAO{};
    GLuint VBO{};


    virtual void loadVertices();
    std::map<std::string, Shader *> shadersMap;
    std::map<std::string, Texture *> texturesMap;

    virtual void setupVertices();
    virtual void loadTransforms();

    BoxCollider* collider;
};

#endif //OPENWORLD_MESH_H
