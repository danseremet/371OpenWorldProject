//
// Created by Mael Semler on 2020-04-06.
//

#include "BranchMesh.h"
#define PI 3.14159265

#include <utility>
using namespace glm;

BranchMesh::BranchMesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, std::vector<int>  tSeed,  std::vector<glm::vec3> positions, std::vector<std::vector<float>> heights)
        : Mesh(std::move(shadersMap), std::move(texturesMap)), seed(tSeed), allPositions(positions), heights(heights) {
}

void BranchMesh::loadVertices() {
    glm::vec3 BROWN = glm::vec3(0.545f, 0.27f, 0.07f);
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
            // positions                            // normals           
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

void BranchMesh::draw() {

    shadersMap["basic"]->use();
    for (auto model : modelMatrices) {
        shadersMap["basic"]->setMat4("worldMatrix", model);
        Mesh::draw();
    }
}

void BranchMesh::toggleShowTexture() {
    showTexture = !showTexture;
}

void BranchMesh::loadTransforms() {
    std::vector<glm::mat4> modelMatrices{ };

    for (GLuint i{ 0 }; i < allPositions.size(); i++) {
        mat4 model{ 1.0f };
        float xPos = allPositions[i].x;
        float zPos = allPositions[i].z;
        float yPos = heights[zPos][xPos];

        numberOfBranches = (seed[i] / 69) % 3;
        size = seed[i] % 3 + 1;
        angleOfBranchY = (seed[i] / 9) % 360;
        angleOfBranchX = ((seed[i] / 11) % 80) + 10;
        angleTree = (seed[i] / 17) % 90;

        //This is the trunk
        model = translate(model, vec3(xPos, yPos + size, zPos));
        model = rotate(model, radians(angleTree), vec3(0.0f, 1.0f, 0.0f));
        model = scale(model, vec3(size / 2, size * 3, size / 2));

        modelMatrices.push_back(model);

        //Draw other branches on the trunk
        if (seed[i] % 2 == 0) {

            size /= 4;
            for (int i = 1; i <= numberOfBranches; i++) {
                angleOfBranchX = fmod((angleOfBranchX * i), 80) + 10;
                angleOfBranchY = fmod((angleOfBranchY * i), 360);
                model = mat4(1.0f);
                model = translate(model, vec3(xPos + (2 * sin(angleOfBranchY * PI / 180) * size), yPos + size + i, zPos + (2 * cos(angleOfBranchY * PI / 180) * size)));
                model = rotate(model, radians(angleOfBranchY), vec3(0.0f, 1.0f, 0.0f));
                model = rotate(model, radians(angleOfBranchX), vec3(1.0f, 0.0f, 0.0f));
                model = scale(model, vec3(size, size * 5, size));


                modelMatrices.push_back(model);
            }
            size *= 4;

        }
    }

    this->modelMatrices = modelMatrices;

  
}
