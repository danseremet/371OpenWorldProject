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
    glm::vec3 BROWN = glm::vec3(0.2f, 0.9f, 0.2f);
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
        {glm::vec3(-0.5f, -0.5f, -0.5f), BROWN, glm::vec3(0.0f,  0.0f, -1.0f)}, // F
        {glm::vec3(0.5f,  0.5f, -0.5f), BROWN, glm::vec3(0.0f,  0.0f, -1.0f)},  // B
        {glm::vec3(0.5f, -0.5f, -0.5f), BROWN, glm::vec3(0.0f,  0.0f, -1.0f)},  // E
        {glm::vec3(0.5f,  0.5f, -0.5f), BROWN, glm::vec3(0.0f,  0.0f, -1.0f)},  // B
        {glm::vec3(-0.5f, -0.5f, -0.5f), BROWN, glm::vec3(0.0f,  0.0f, -1.0f)}, // F
        {glm::vec3(-0.5f,  0.5f, -0.5f), BROWN, glm::vec3(0.0f,  0.0f, -1.0f)}, // C
        // FRONT
        {glm::vec3(-0.5f, -0.5f,  0.5f), BROWN, glm::vec3(0.0f,  0.0f,  1.0f)}, // G
        {glm::vec3(0.5f, -0.5f,  0.5f), BROWN, glm::vec3(0.0f,  0.0f,  1.0f)},  // H
        {glm::vec3(0.5f,  0.5f,  0.5f), BROWN, glm::vec3(0.0f,  0.0f,  1.0f)},  // A
        {glm::vec3(0.5f,  0.5f,  0.5f), BROWN, glm::vec3(0.0f,  0.0f,  1.0f)},  // A
        {glm::vec3(-0.5f,  0.5f,  0.5f), BROWN, glm::vec3(0.0f,  0.0f,  1.0f)}, // D
        {glm::vec3(-0.5f, -0.5f,  0.5f), BROWN, glm::vec3(0.0f,  0.0f,  1.0f)}, // G
        // LEFT
        {glm::vec3(-0.5f,  0.5f,  0.5f), BROWN, glm::vec3(-1.0f,  0.0f,  0.0f)},// D
        {glm::vec3(-0.5f,  0.5f, -0.5f), BROWN, glm::vec3(-1.0f,  0.0f,  0.0f)},// C
        {glm::vec3(-0.5f, -0.5f, -0.5f), BROWN, glm::vec3(-1.0f,  0.0f,  0.0f)},// F
        {glm::vec3(-0.5f, -0.5f, -0.5f), BROWN, glm::vec3(-1.0f,  0.0f,  0.0f)},// F
        {glm::vec3(-0.5f, -0.5f,  0.5f), BROWN, glm::vec3(-1.0f,  0.0f,  0.0f)},// G
        {glm::vec3(-0.5f,  0.5f,  0.5f), BROWN, glm::vec3(-1.0f,  0.0f,  0.0f)},// D
        // RIGHT
        {glm::vec3(0.5f,  0.5f,  0.5f), BROWN, glm::vec3(1.0f,  0.0f,  0.0f)},  // A
        {glm::vec3(0.5f, -0.5f, -0.5f), BROWN, glm::vec3(1.0f,  0.0f,  0.0f)},  // E
        {glm::vec3(0.5f,  0.5f, -0.5f), BROWN, glm::vec3(1.0f,  0.0f,  0.0f)},  // B
        {glm::vec3(0.5f, -0.5f, -0.5f), BROWN, glm::vec3(1.0f,  0.0f,  0.0f)},  // E
        {glm::vec3(0.5f,  0.5f,  0.5f), BROWN, glm::vec3(1.0f,  0.0f,  0.0f)},  // A
        {glm::vec3(0.5f, -0.5f,  0.5f), BROWN, glm::vec3(1.0f,  0.0f,  0.0f)},  // H
        // BOTTOM
        {glm::vec3(-0.5f, -0.5f, -0.5f), BROWN, glm::vec3(0.0f, -1.0f,  0.0f)}, // F
        {glm::vec3(0.5f, -0.5f, -0.5f), BROWN, glm::vec3(0.0f, -1.0f,  0.0f)},  // E
        {glm::vec3(0.5f, -0.5f,  0.5f), BROWN, glm::vec3(0.0f, -1.0f,  0.0f)},  // H
        {glm::vec3(0.5f, -0.5f,  0.5f), BROWN, glm::vec3(0.0f, -1.0f,  0.0f)},  // H
        {glm::vec3(-0.5f, -0.5f,  0.5f), BROWN, glm::vec3(0.0f, -1.0f,  0.0f)}, // G
        {glm::vec3(-0.5f, -0.5f, -0.5f), BROWN, glm::vec3(0.0f, -1.0f,  0.0f)}, // F
        // UP
        {glm::vec3(-0.5f,  0.5f, -0.5f), BROWN, glm::vec3(0.0f,  1.0f,  0.0f)}, // C
        {glm::vec3(0.5f,  0.5f,  0.5f), BROWN, glm::vec3(0.0f,  1.0f,  0.0f)},  // A
        {glm::vec3(0.5f,  0.5f, -0.5f), BROWN, glm::vec3(0.0f,  1.0f,  0.0f)},  // B
        {glm::vec3(0.5f,  0.5f,  0.5f), BROWN, glm::vec3(0.0f,  1.0f,  0.0f)},  // A
        {glm::vec3(-0.5f,  0.5f, -0.5f), BROWN, glm::vec3(0.0f,  1.0f,  0.0f)}, // C
        {glm::vec3(-0.5f,  0.5f,  0.5f), BROWN, glm::vec3(0.0f,  1.0f,  0.0f)}  // D
    };
}

void LeavesMesh::draw() {
    mat4 baseplate{mat4(1.0f)};
    baseplate = translate(baseplate, vec3(0.0f, 4.0f, 0.0f));
    baseplate = scale(baseplate, vec3(2.0f, 2.0f, 2.0f));


    shadersMap["basic"]->use();
    shadersMap["basic"]->setMat4("worldMatrix", baseplate);

    Mesh::draw();
}

void LeavesMesh::toggleShowTexture() {
    showTexture = !showTexture;
}
