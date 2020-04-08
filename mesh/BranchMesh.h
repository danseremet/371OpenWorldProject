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

    int numberOfBranches;

    float size;

    float angleOfBranchY;

    float angleOfBranchX;

    float angleTree;

public:
    BranchMesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, std::vector<int>  tSeed, std::vector<glm::vec3> positions);


    void draw() override;

    void toggleShowTexture();
};



#endif //OPENWORLD_BRANCHMESH_H
