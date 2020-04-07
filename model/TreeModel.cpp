//
// Created by danseremet on 2020-04-04.
//

#include "TreeModel.h"

#include <utility>

TreeModel::TreeModel(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, GLint tNumber) :
        Model(std::move(shadersMap), std::move(texturesMap)), treeNumber(tNumber) {
}

void TreeModel::loadMeshes() {
    auto *branchMesh = new BranchMesh{shadersMap, texturesMap};
    branchMesh->loadMesh();
    meshes.push_back(branchMesh);

    if (treeNumber == 1) {
        auto* leaveMesh = new LeavesMesh{ shadersMap, texturesMap };
        leaveMesh->loadMesh();
        meshes.push_back(leaveMesh);
    }
    else {
        auto* leaveMesh = new Leaves2Mesh{shadersMap, texturesMap};
        leaveMesh->loadMesh();
        meshes.push_back(leaveMesh);
    }

    
}