//
// Created by danseremet on 2020-04-04.
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
    TreeModel(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, int treeNumber);

    void loadMeshes() override;
};



#endif //OPENWORLD_TREEMODEL_H
