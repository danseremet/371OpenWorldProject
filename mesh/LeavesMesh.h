//
// Created by Mael Semler on 2020-04-06.
//

#ifndef OPENWORLD_LEAVESMODEL_H
#define OPENWORLD_LEAVESMODEL_H


#include "Mesh.h"

class LeavesMesh: public Mesh {

private:
    void loadVertices() override;

    GLboolean showTexture{true};

    std::vector<glm::vec3> allPositions;

public:
    LeavesMesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, std::vector<int>  tSeed, std::vector<glm::vec3> positions);

    std::vector<int>  seed;

    void draw() override;

    void toggleShowTexture();

    void loadTransforms() override;
};



#endif //OPENWORLD_LEAVESMODEL_H
