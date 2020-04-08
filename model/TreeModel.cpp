//
// Created by Mael Semler on 2020-04-06.
//

#include "TreeModel.h"

#include <utility>

TreeModel::TreeModel(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, std::vector<int> tNumber, std::vector<glm::vec3> positions, std::vector<std::vector<float>> heights) :
        Model(std::move(shadersMap), std::move(texturesMap)), treeNumber(tNumber), allPositions(positions), heights(heights) {
}

void TreeModel::loadMeshes() {
    
    //Create the BranchMesh
    auto* branchMesh = new BranchMesh{ shadersMap, texturesMap, treeNumber, allPositions, heights};
    branchMesh->loadMesh();
    meshes.push_back(branchMesh);

    auto* leaveMesh = new LeavesMesh{ shadersMap, texturesMap, treeNumber, allPositions, heights };
    leaveMesh->loadMesh();
    meshes.push_back(leaveMesh);

    auto* leaveMesh2 = new Leaves2Mesh{shadersMap, texturesMap, treeNumber, allPositions, heights };
    leaveMesh2->loadMesh();
    meshes.push_back(leaveMesh2);

    
}

void TreeModel::setTreeNumber() {
   // treeNumber = (rand() * 100000) % 9999999;
    meshes.clear();
    loadMeshes();
}