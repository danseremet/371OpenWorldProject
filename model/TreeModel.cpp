//
// Created by danseremet on 2020-04-04.
//

#include "TreeModel.h"

#include <utility>

TreeModel::TreeModel(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap) :
        Model(std::move(shadersMap), std::move(texturesMap)) {
}

void TreeModel::loadMeshes() {
    auto *branchMesh = new BranchMesh{shadersMap, texturesMap};
    branchMesh->loadMesh();
    meshes.push_back(branchMesh);

    auto* leaveMesh = new LeavesMesh{shadersMap, texturesMap};
    leaveMesh->loadMesh();
    meshes.push_back(leaveMesh);
}
