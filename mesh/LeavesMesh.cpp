//
// Created by Mael Semler on 2020-04-06.
//

#include "LeavesMesh.h"
#define PI 3.14159265


#include <utility>

using namespace glm;

LeavesMesh::LeavesMesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, std::vector<int>  tSeed, std::vector<glm::vec3> positions)
        : Mesh(std::move(shadersMap), std::move(texturesMap)), seed(tSeed), allPositions(positions) {
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
    mat4 baseplate{ mat4(1.0f) };
    shadersMap["basic"]->use();

    float xPos;
    float yPos;
    float zPos;

    for (GLuint i{ 0 }; i < allPositions.size(); i++) {
        if (seed[i] % 2 == 0) {
            xPos = allPositions[i].x;
            yPos = allPositions[i].y;
            zPos = allPositions[i].z;

            numberOfLeaves = (seed[i] / 69) % 3;
            size = seed[i] % 3 + 1;
            angleOfBranchY = (seed[i] / 9) % 360;
            angleOfBranchX = ((seed[i] / 11) % 80) + 10;
            angleTree = (seed[i] / 17) % 90;

            //main leaves
            baseplate = translate(baseplate, vec3(xPos, yPos + (size * 2.0f), zPos));
            baseplate = rotate(baseplate, radians(angleTree), vec3(0.0f, 1.0f, 0.0f));
            baseplate = scale(baseplate, vec3(size * 2, size * 2, size * 2));
            shadersMap["basic"]->setMat4("worldMatrix", baseplate);
            Mesh::draw();

            //small leaves
            for (int i = 1; i <= numberOfLeaves; i++) {
                angleOfBranchX = fmod((angleOfBranchX * i), 80) + 10;
                angleOfBranchY = fmod((angleOfBranchY * i), 360);
                baseplate = mat4(1.0f);
                baseplate = translate(baseplate, vec3(xPos + (size * sin(angleOfBranchY * PI / 180)), (size * cos(angleOfBranchX * PI / 180)) + i + yPos - 1.0f, zPos + (size * cos(angleOfBranchY * PI / 180))));
                baseplate = rotate(baseplate, radians(angleOfBranchY), vec3(0.0f, 1.0f, 0.0f));
                baseplate = rotate(baseplate, radians(angleOfBranchX), vec3(1.0f, 0.0f, 0.0f));
                baseplate = scale(baseplate, vec3(size, size, size));


                shadersMap["basic"]->setMat4("worldMatrix", baseplate);

                Mesh::draw();
            }
            baseplate = mat4(1.0f);
        }
        
    }

    
}

void LeavesMesh::toggleShowTexture() {
    showTexture = !showTexture;
}

void LeavesMesh::loadTransforms() {

}
