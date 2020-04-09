//
// Created by Mael Semler on 2020-04-06.
//

#include "LeavesMesh.h"
#define PI 3.14159265


#include <utility>

using namespace glm;

LeavesMesh::LeavesMesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, std::vector<int>  tSeed, std::vector<glm::vec3> positions, int chunkX, int chunkZ, int chunkSize, std::vector<std::vector<float>> heights)
        : Mesh(std::move(shadersMap), std::move(texturesMap)), seed(tSeed), allPositions(positions), chunkX(chunkX), chunkZ(chunkZ), chunkSize(chunkSize), heights(heights) {
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
    shadersMap["basic"]->use();
    for (auto model : modelMatrices) {
        shadersMap["basic"]->setMat4("worldMatrix", model);
        Mesh::draw();
    }

}

void LeavesMesh::toggleShowTexture() {
    showTexture = !showTexture;
}

void LeavesMesh::loadTransforms() {
    std::vector<glm::mat4> modelMatrices{ };

    for (GLuint i{ 0 }; i < allPositions.size(); i++) {
        mat4 model{ 1.0f };

        if (seed[i] % 2 == 0) {
            int dx = chunkSize * chunkX;
            int dz = chunkSize * chunkZ;

            float xPos = allPositions[i].x;
            float zPos = allPositions[i].z;
            float yPos = heights[zPos][xPos];
            xPos += dx;
            zPos += dz;

            numberOfLeaves = (seed[i] / 69) % 3;
            size = seed[i] % 3 + 1;
            angleOfBranchY = (seed[i] / 9) % 360;
            angleOfBranchX = ((seed[i] / 11) % 80) + 10;
            angleTree = (seed[i] / 17) % 90;

            //main leaves
            model = translate(model, vec3(xPos, yPos + (size * 2.0f), zPos));
            model = rotate(model, radians(angleTree), vec3(0.0f, 1.0f, 0.0f));
            model = scale(model, vec3(size * 2, size * 2, size * 2));

            modelMatrices.push_back(model);

            //small leaves
            for (int i = 1; i <= numberOfLeaves; i++) {
                angleOfBranchX = fmod((angleOfBranchX * i), 80) + 10;
                angleOfBranchY = fmod((angleOfBranchY * i), 360);
                model = mat4(1.0f);
                model = translate(model, vec3(xPos + (size * sin(angleOfBranchY * PI / 180)), (size * cos(angleOfBranchX * PI / 180)) + yPos + i, zPos + (size * cos(angleOfBranchY * PI / 180))));
                model = rotate(model, radians(angleOfBranchY), vec3(0.0f, 1.0f, 0.0f));
                model = rotate(model, radians(angleOfBranchX), vec3(1.0f, 0.0f, 0.0f));
                model = scale(model, vec3(size, size, size));

                modelMatrices.push_back(model);
            }
        }

    }

    this->modelMatrices = modelMatrices;
}
