//
// Created by Mael Semler on 2020-04-06.
//

#include "Leaves2Mesh.h"


#include <utility>

using namespace glm;

Leaves2Mesh::Leaves2Mesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, std::vector<int>  tSeed, std::vector<glm::vec3> positions, std::vector<std::vector<float>> heights)
        : Mesh(std::move(shadersMap), std::move(texturesMap)), seed(tSeed), allPositions(positions), heights(heights) {
}

void Leaves2Mesh::loadVertices() {
    glm::vec3 BROWN = glm::vec3(0.0f, 0.35f, 0.25f);
    vertices = {
       
        // positions          // normals           
        // BACK
        {glm::vec3(-0.5f, -0.5f, -0.5f), BROWN, glm::vec3(0.0f,  0.5f, -1.0f)}, // F
        {glm::vec3(0.0f,  0.5f, 0.0f), BROWN, glm::vec3(0.0f,  0.5f, -1.0f)},  // A
        {glm::vec3(0.5f, -0.5f, -0.5f), BROWN, glm::vec3(0.0f,  0.5f, -1.0f)},  // E
        // FRONT
        {glm::vec3(-0.5f, -0.5f,  0.5f), BROWN, glm::vec3(0.0f,  0.5f,  1.0f)}, // G
        {glm::vec3(0.5f, -0.5f,  0.5f), BROWN, glm::vec3(0.0f,  0.5f,  1.0f)},  // H
        {glm::vec3(0.0f,  0.5f,  0.0f), BROWN, glm::vec3(0.0f,  0.5f,  1.0f)},  // A
        // LEFT
        {glm::vec3(-0.5f, -0.5f, -0.5f), BROWN, glm::vec3(-1.0f,  0.5f,  0.0f)},// F
        {glm::vec3(-0.5f, -0.5f,  0.5f), BROWN, glm::vec3(-1.0f,  0.5f,  0.0f)},// G
        {glm::vec3(0.0f,  0.5f,  0.0f), BROWN, glm::vec3(-1.0f,  0.5f,  0.0f)},// A
        // RIGHT
        {glm::vec3(0.5f, -0.5f, -0.5f), BROWN, glm::vec3(1.0f,  0.5f,  0.0f)},  // E
        {glm::vec3(0.0f,  0.5f,  0.0f), BROWN, glm::vec3(1.0f,  0.5f,  0.0f)},  // A
        {glm::vec3(0.5f, -0.5f,  0.5f), BROWN, glm::vec3(1.0f,  0.5f,  0.0f)},  // H
        // BOTTOM
        {glm::vec3(-0.5f, -0.5f, -0.5f), BROWN, glm::vec3(0.0f, -1.0f,  0.0f)}, // F
        {glm::vec3(0.5f, -0.5f, -0.5f), BROWN, glm::vec3(0.0f, -1.0f,  0.0f)},  // E
        {glm::vec3(0.5f, -0.5f,  0.5f), BROWN, glm::vec3(0.0f, -1.0f,  0.0f)},  // H
        {glm::vec3(0.5f, -0.5f,  0.5f), BROWN, glm::vec3(0.0f, -1.0f,  0.0f)},  // H
        {glm::vec3(-0.5f, -0.5f,  0.5f), BROWN, glm::vec3(0.0f, -1.0f,  0.0f)}, // G
        {glm::vec3(-0.5f, -0.5f, -0.5f), BROWN, glm::vec3(0.0f, -1.0f,  0.0f)}, // F
    };
}

void Leaves2Mesh::draw() {
    shadersMap["basic"]->use();
    for (auto model : modelMatrices) {
        shadersMap["basic"]->setMat4("worldMatrix", model);
        Mesh::draw();
    }  
}

void Leaves2Mesh::toggleShowTexture() {
    showTexture = !showTexture;
}

void Leaves2Mesh::loadTransforms() {
    std::vector<glm::mat4> modelMatrices{ };

    for (GLuint i{ 0 }; i < allPositions.size(); i++) {
        mat4 model{ 1.0f };

        if (seed[i] % 2 != 0) {
            float xPos = allPositions[i].x;
            float zPos = allPositions[i].z;
            float yPos = heights[zPos][xPos];

            leavesSize = (seed[i] % 4) + 1;
            size = seed[i] % 3 + 1;
            numberOfLeaves = ((seed[i] / 10) % 5) + 1;
            angleTree = (seed[i] / 17) % 90;

            for (int i = 1; i <= numberOfLeaves; i++) {
                model = mat4(1.0f);
                model = translate(model, vec3(xPos, (size * 2.0f) + (i * leavesSize / 2) + yPos + size - 2.0f, zPos));
                model = rotate(model, radians(angleTree), vec3(0.0f, 1.0f, 0.0f));
                model = scale(model, vec3(leavesSize, leavesSize, leavesSize));

                modelMatrices.push_back(model);
            }
        }
    }
    this->modelMatrices = modelMatrices;
}