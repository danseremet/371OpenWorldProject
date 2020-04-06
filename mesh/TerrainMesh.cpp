//
// Created by danseremet on 2020-04-04.
//

#include "TerrainMesh.h"


#include <utility>

using namespace glm;

TerrainMesh::TerrainMesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap)
        : Mesh(std::move(shadersMap), std::move(texturesMap)) {
}

void TerrainMesh::loadVertices() {
    glm::vec3 GREEN = glm::vec3(0.2f, 0.6f, 0.3f);
    glm::vec3 BLUE = glm::vec3(0.2f, 0.2f, 0.7f);

    // top_left k0     top_right k1
    //     |-----------
    //     |        /
    //     |      /
    //     |    /
    //     |  /
    //     |/         |
    // bottom_left k2   bottom_right k3

    vec3 top_left = vec3(0.0f, 0.0f, 0.0f);
    vec3 bottom_left = vec3(0.0f, 0.0f, 1.0f);
    vec3 top_right = vec3(1.0f, 0.0f, 0.0f);
    vec3 bottom_right = vec3(1.0f, 0.0f, 1.0f);

    vec3 normal = vec3(0.0f, 0.0f, 0.0f);

    Vertex L0 = {top_left, GREEN, normal};
    Vertex L1 = {top_right, GREEN,normal};
    Vertex R1 = {top_right, BLUE, normal};
    Vertex L2 = {bottom_left, GREEN, normal};
    Vertex R2 = {bottom_left, BLUE, normal};
    Vertex R3 = {bottom_right, BLUE, normal};

    vertices = {
            L0,
            L2,
            L1,

            R1,
            R2,
            R3
    };

    for (int z{0}; z < 10; z += 1) {

        for (int x{0}; x < 10; x += 1) {
            glm::vec3 translation{};
            translation.x = (float)x;
            translation.z = (float)z;
            translations.push_back(translation);
        }

    }


}

void TerrainMesh::setupVertices() { // cube mesh
    // vao
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // instance data
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 100, &translations[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vertex vbo
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) nullptr);
    glEnableVertexAttribArray(0);
    // vertex color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) sizeof(glm::vec3));
    glEnableVertexAttribArray(1);
    // vertex normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);
    // instance data
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(3, 1); // tell OpenGL this is an instanced vertex attribute.




    glBindVertexArray(0);
}

void TerrainMesh::draw() {
    shadersMap["terrain"]->use();

    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, vertices.size(), 100);
//    glBindVertexArray(0);
}

void TerrainMesh::toggleShowTexture() {
    showTexture = !showTexture;
}
