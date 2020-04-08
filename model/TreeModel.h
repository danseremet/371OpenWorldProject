//
// Created by Mael Semler on 2020-04-06.
//

#ifndef OPENWORLD_TREEMODEL_H
#define OPENWORLD_TREEMODEL_H



#include "Model.h"
#include "../mesh/BranchMesh.h"
#include "../mesh/LeavesMesh.h"
#include "../mesh/Leaves2Mesh.h"
#include "../texture/Texture.h"

class TreeModel: public Model {
public:
    TreeModel(std::map<std::string, Shader*> shadersMap, std::map<std::string, Texture*> texturesMap, std::vector<int>  tNumber, std::vector<glm::vec3> positions, std::vector<std::vector<float>> heights);

    void loadMeshes() override;

    void setTreeNumber();

private:
    std::vector<int>  treeNumber;

    std::vector<glm::vec3> allPositions;

    std::vector<std::vector<float>> heights;
};



#endif //OPENWORLD_TREEMODEL_H
