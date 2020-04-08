//
// Created by Mael Semler on 2020-04-06.
//

#ifndef OPENWORLD_LEAVESMODEL_H
#define OPENWORLD_LEAVESMODEL_H


#include "Mesh.h"

class LeavesMesh: public Mesh {

private:
    void loadVertices() override;

    void loadTransforms() override;

    std::vector<glm::mat4> modelMatrices;

    GLboolean showTexture{true};

    std::vector<glm::vec3> allPositions;

    int numberOfLeaves;

    float size;

    float angleOfBranchY;

    float angleOfBranchX;

    float angleTree;

    std::vector<std::vector<float>> heights;

    int chunkX;

    int chunkZ;

    int chunkSize;

public:
    LeavesMesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, std::vector<int>  tSeed, std::vector<glm::vec3> positions, int chunkX, int chunkZ, int chunkSize, std::vector<std::vector<float>> heights);

    std::vector<int>  seed;

    void draw() override;

    void toggleShowTexture();

};



#endif //OPENWORLD_LEAVESMODEL_H
