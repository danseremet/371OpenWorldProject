//
// Created by Mael Semler on 2020-04-06.
//

#include "Leaves2Mesh.h"


#include <utility>

using namespace glm;

Leaves2Mesh::Leaves2Mesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, std::vector<int>  tSeed, std::vector<glm::vec3> positions)
        : Mesh(std::move(shadersMap), std::move(texturesMap)), seed(tSeed), allPositions(positions) {
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
    mat4 baseplate{ mat4(1.0f) };
    shadersMap["basic"]->use();
    float xPos;
    float yPos;
    float zPos;

    for (GLuint i{ 0 }; i < allPositions.size(); i++) {
        if (seed[i] % 2 != 0) {
            xPos = allPositions[i].x;
            yPos = allPositions[i].y;
            zPos = allPositions[i].z;

            leavesSize = (seed[i] % 4) + 1;
            size = seed[i] % 3 + 1;
            numberOfLeaves = ((seed[i] / 10) % 5) + 1;
            angleTree = (seed[i] / 17) % 90;

            for (int i = 1; i <= numberOfLeaves; i++) {
                baseplate = mat4(1.0f);
                baseplate = translate(baseplate, vec3(xPos, (size * 2.0f) + (i * leavesSize / 2) + yPos - 2.0f, zPos));
                baseplate = rotate(baseplate, radians(angleTree), vec3(0.0f, 1.0f, 0.0f));
                baseplate = scale(baseplate, vec3(leavesSize, leavesSize, leavesSize));

                shadersMap["basic"]->setMat4("worldMatrix", baseplate);
                Mesh::draw();
            }
        }
        

    }
    
    

}

void Leaves2Mesh::toggleShowTexture() {
    showTexture = !showTexture;
}