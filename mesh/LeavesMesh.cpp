//
// Created by danseremet on 2020-04-04.
//

#include "LeavesMesh.h"


#include <utility>

using namespace glm;

LeavesMesh::LeavesMesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap)
        : Mesh(std::move(shadersMap), std::move(texturesMap)) {
}

void LeavesMesh::loadVertices() {
    glm::vec3 GREEN = glm::vec3(0.9f, 0.0f, 0.0f);
    vertices = {
            {vec3(0.0f, 0.0f, 0.0f), GREEN, vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 1.0f)}, // top left
            {vec3(0.0f, 0.0f, 1.0f), GREEN, vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)}, // bottom left
            {vec3(1.0f, 0.0f, 0.0f), GREEN, vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)}, // top right

            {vec3(1.0f, 0.0f, 0.0f), GREEN, vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 1.0f)}, // top right
            {vec3(0.0f, 0.0f, 1.0f), GREEN, vec3(0.0f, 1.0f, 0.0f), vec2(0.0f, 0.0f)}, // bottom left
            {vec3(1.0f, 0.0f, 1.0f), GREEN, vec3(0.0f, 1.0f, 0.0f), vec2(1.0f, 0.0f)}, // bottom right
    };
}

void LeavesMesh::draw() {
    mat4 baseplate{mat4(1.0f)};
    baseplate = translate(baseplate, vec3(-50.0f, 1.0f, -50.0f));
    baseplate = scale(baseplate, vec3(100.0f, 0.0f, 10.0f));


    shadersMap["basic"]->use();
    shadersMap["basic"]->setMat4("worldMatrix", baseplate);

    Mesh::draw();
}

void LeavesMesh::toggleShowTexture() {
    showTexture = !showTexture;
}
