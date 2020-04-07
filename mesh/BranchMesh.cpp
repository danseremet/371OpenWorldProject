//
// Created by Mael Semler on 2020-04-06.
//

#include "BranchMesh.h"
#define PI 3.14159265

#include <utility>
using namespace glm;

BranchMesh::BranchMesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, std::vector<int>  tSeed,  std::vector<glm::vec3> positions, GLboolean oTrunk)
        : Mesh(std::move(shadersMap), std::move(texturesMap)), seed(tSeed), allPositions(positions), onlyTrunk(oTrunk) {
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

void BranchMesh::draw() {

    int numberOfBranches;
    float size;
    float angleOfBranchY;
    float angleOfBranchX;

    mat4 baseplate{ mat4(1.0f) };
    shadersMap["basic"]->use();
    
    float xPos;
    float yPos;
    float zPos;

    for (GLuint i{ 0 }; i < allPositions.size(); i++) {
        xPos = allPositions[i].x;
        yPos = allPositions[i].y;
        zPos = allPositions[i].z;

        numberOfBranches = (seed[i] / 69) % 3;
        size = seed[i] % 2 + 1;
        angleOfBranchY = (seed[i] / 9) % 360;
        angleOfBranchX = ((seed[i] / 11) % 80) + 10;
        
        //This is the trunk
        baseplate = translate(baseplate, vec3(xPos, yPos, zPos));
        baseplate = scale(baseplate, vec3(size / 2, size * 3, size / 2));

       
        shadersMap["basic"]->setMat4("worldMatrix", baseplate);
        Mesh::draw();

       
        //Draw other branches on the trunk
       if (seed[i] % 2 == 0) {
             size /= 4;
            for (int i = 1; i <= numberOfBranches; i++) {
                angleOfBranchX = fmod((angleOfBranchX * i), 80) + 10;
                angleOfBranchY = fmod((angleOfBranchY * i), 360);
                baseplate = mat4(1.0f);
                baseplate = translate(baseplate, vec3(xPos + (2 * sin(angleOfBranchY * PI / 180) * size), yPos-1.0f + i, zPos + (2 * cos(angleOfBranchY * PI / 180) * size)));
                baseplate = rotate(baseplate, radians(angleOfBranchY), vec3(0.0f, 1.0f, 0.0f));
                baseplate = rotate(baseplate, radians(angleOfBranchX), vec3(1.0f, 0.0f, 0.0f));
                baseplate = scale(baseplate, vec3(size, size * 5, size));


                shadersMap["basic"]->setMat4("worldMatrix", baseplate);

                Mesh::draw();
            }
             size *= 4;
        
       }
       baseplate = mat4(1.0f);
       

    }

    
   
    
   
}

void BranchMesh::toggleShowTexture() {
    showTexture = !showTexture;
}
