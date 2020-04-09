//
// Created by Mael Semler on 2020-04-06.
//

#ifndef OPENWORLD_BRANCHMESH_H
#define OPENWORLD_BRANCHMESH_H


#include "Mesh.h"

class BranchMesh: public Mesh {

private:
    void loadVertices() override;

    void loadTransforms() override;

    GLboolean showTexture{true};

    std::vector<glm::mat4> modelMatrices;

    std::vector<int>  seed;

    std::vector<glm::vec3> allPositions;

    glm::vec2 chunkPosition;

    std::vector<std::vector<float>> heights;

    int numberOfBranches;

    float size;

    float angleOfBranchY;

    float angleOfBranchX;

    float angleTree;

    int chunkX;

    int chunkZ;

    int chunkSize;

public:
    BranchMesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, std::vector<int>  tSeed, std::vector<glm::vec3> positions, int chunkX, int chunkZ, int chunkSize, std::vector<std::vector<float>> heights);


    void draw() override;

    void toggleShowTexture();
};



#endif //OPENWORLD_BRANCHMESH_H
