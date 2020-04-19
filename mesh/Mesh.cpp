//
// Created by danseremet on 2020-04-04.
//

#include "Mesh.h"


Mesh::Mesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap):
        shadersMap{std::move(shadersMap)}, texturesMap{std::move(texturesMap)} {
}

void Mesh::loadMesh() {
    loadVertices();
    setupVertices();
    loadTransforms();
}

std::vector<Vertex> Mesh::returnVertices() {
    return vertices;
}
void Mesh::loadVertices() {
    glm::vec3 BLUE = glm::vec3(0.0f, 0.0f, 0.5f);
    vertices = {
            //  CUBE VERTICES
            //
            //      C ------- B
            //     /|        /|
            //    / |       / |
            //   /  |      /  |
            //  D --|---- A   |
            //  |   F ----|-- E
            //  |  /      |  /
            //  | /       | /
            //  |/        |/
            //  G ------- H
            //
            // positions          // normals           // texture coords
            // BACK
            {glm::vec3(-0.5f, -0.5f, -0.5f), BLUE, glm::vec3(0.0f,  0.0f, -1.0f)}, // F
            {glm::vec3(0.5f,  0.5f, -0.5f), BLUE, glm::vec3(0.0f,  0.0f, -1.0f)},  // B
            {glm::vec3(0.5f, -0.5f, -0.5f), BLUE, glm::vec3(0.0f,  0.0f, -1.0f)},  // E
            {glm::vec3(0.5f,  0.5f, -0.5f), BLUE, glm::vec3(0.0f,  0.0f, -1.0f)},  // B
            {glm::vec3(-0.5f, -0.5f, -0.5f), BLUE, glm::vec3(0.0f,  0.0f, -1.0f)}, // F
            {glm::vec3(-0.5f,  0.5f, -0.5f), BLUE, glm::vec3(0.0f,  0.0f, -1.0f)}, // C
            // FRONT
            {glm::vec3(-0.5f, -0.5f,  0.5f), BLUE, glm::vec3(0.0f,  0.0f,  1.0f)}, // G
            {glm::vec3(0.5f, -0.5f,  0.5f), BLUE, glm::vec3(0.0f,  0.0f,  1.0f)},  // H
            {glm::vec3(0.5f,  0.5f,  0.5f), BLUE, glm::vec3(0.0f,  0.0f,  1.0f)},  // A
            {glm::vec3(0.5f,  0.5f,  0.5f), BLUE, glm::vec3(0.0f,  0.0f,  1.0f)},  // A
            {glm::vec3(-0.5f,  0.5f,  0.5f), BLUE, glm::vec3(0.0f,  0.0f,  1.0f)}, // D
            {glm::vec3(-0.5f, -0.5f,  0.5f), BLUE, glm::vec3(0.0f,  0.0f,  1.0f)}, // G
            // LEFT
            {glm::vec3(-0.5f,  0.5f,  0.5f), BLUE, glm::vec3(-1.0f,  0.0f,  0.0f)},// D
            {glm::vec3(-0.5f,  0.5f, -0.5f), BLUE, glm::vec3(-1.0f,  0.0f,  0.0f)},// C
            {glm::vec3(-0.5f, -0.5f, -0.5f), BLUE, glm::vec3(-1.0f,  0.0f,  0.0f)},// F
            {glm::vec3(-0.5f, -0.5f, -0.5f), BLUE, glm::vec3(-1.0f,  0.0f,  0.0f)},// F
            {glm::vec3(-0.5f, -0.5f,  0.5f), BLUE, glm::vec3(-1.0f,  0.0f,  0.0f)},// G
            {glm::vec3(-0.5f,  0.5f,  0.5f), BLUE, glm::vec3(-1.0f,  0.0f,  0.0f)},// D
            // RIGHT
            {glm::vec3(0.5f,  0.5f,  0.5f), BLUE, glm::vec3(1.0f,  0.0f,  0.0f)},  // A
            {glm::vec3(0.5f, -0.5f, -0.5f), BLUE, glm::vec3(1.0f,  0.0f,  0.0f)},  // E
            {glm::vec3(0.5f,  0.5f, -0.5f), BLUE, glm::vec3(1.0f,  0.0f,  0.0f)},  // B
            {glm::vec3(0.5f, -0.5f, -0.5f), BLUE, glm::vec3(1.0f,  0.0f,  0.0f)},  // E
            {glm::vec3(0.5f,  0.5f,  0.5f), BLUE, glm::vec3(1.0f,  0.0f,  0.0f)},  // A
            {glm::vec3(0.5f, -0.5f,  0.5f), BLUE, glm::vec3(1.0f,  0.0f,  0.0f)},  // H
            // BOTTOM
            {glm::vec3(-0.5f, -0.5f, -0.5f), BLUE, glm::vec3(0.0f, -1.0f,  0.0f)}, // F
            {glm::vec3(0.5f, -0.5f, -0.5f), BLUE, glm::vec3(0.0f, -1.0f,  0.0f)},  // E
            {glm::vec3(0.5f, -0.5f,  0.5f), BLUE, glm::vec3(0.0f, -1.0f,  0.0f)},  // H
            {glm::vec3(0.5f, -0.5f,  0.5f), BLUE, glm::vec3(0.0f, -1.0f,  0.0f)},  // H
            {glm::vec3(-0.5f, -0.5f,  0.5f), BLUE, glm::vec3(0.0f, -1.0f,  0.0f)}, // G
            {glm::vec3(-0.5f, -0.5f, -0.5f), BLUE, glm::vec3(0.0f, -1.0f,  0.0f)}, // F
            // UP
            {glm::vec3(-0.5f,  0.5f, -0.5f), BLUE, glm::vec3(0.0f,  1.0f,  0.0f)}, // C
            {glm::vec3(0.5f,  0.5f,  0.5f), BLUE, glm::vec3(0.0f,  1.0f,  0.0f)},  // A
            {glm::vec3(0.5f,  0.5f, -0.5f), BLUE, glm::vec3(0.0f,  1.0f,  0.0f)},  // B
            {glm::vec3(0.5f,  0.5f,  0.5f), BLUE, glm::vec3(0.0f,  1.0f,  0.0f)},  // A
            {glm::vec3(-0.5f,  0.5f, -0.5f), BLUE, glm::vec3(0.0f,  1.0f,  0.0f)}, // C
            {glm::vec3(-0.5f,  0.5f,  0.5f), BLUE, glm::vec3(0.0f,  1.0f,  0.0f)}  // D
    };
}

void Mesh::setupVertices() { // cube mesh
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

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


    glBindVertexArray(0);
}

void Mesh::draw() { // cube draw
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void Mesh::loadTransforms() {

}
