//
// Created by Mael Semler on 2020-04-06.
//

#include "TreeModel.h"

#include <utility>
#include <ctime>

int TreeModel::seed = time(0);

TreeModel::TreeModel(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, int chunkX, int chunkZ, int chunkSize, std::vector<std::vector<float>> heights, int numberOfTrees) :
        Model(std::move(shadersMap), std::move(texturesMap)), chunkX(chunkX), chunkZ(chunkZ), chunkSize(chunkSize), heights(heights), numberOfTrees(numberOfTrees){
}

void TreeModel::loadMeshes() {

    std::vector<glm::vec3> treePositions = generateTreesFor1Chunk();

    std::vector<int> treeSeed = populateTreeSeeds();
    
    //Create the BranchMesh
    auto* branchMesh = new BranchMesh{ shadersMap, texturesMap, treeSeed, treePositions, chunkX, chunkZ, chunkSize, heights};
    branchMesh->loadMesh();
    meshes.push_back(branchMesh);

    auto* leaveMesh = new LeavesMesh{ shadersMap, texturesMap, treeSeed, treePositions, chunkX, chunkZ, chunkSize, heights };
    leaveMesh->loadMesh();
    meshes.push_back(leaveMesh);

    auto* leaveMesh2 = new Leaves2Mesh{shadersMap, texturesMap, treeSeed, treePositions, chunkX, chunkZ, chunkSize, heights };
    leaveMesh2->loadMesh();
    meshes.push_back(leaveMesh2);

    
}

void TreeModel::setTreeNumber() {
   // treeNumber = (rand() * 100000) % 9999999;
    meshes.clear();
    loadMeshes();
}

float TreeModel::randomFloat(float from = 0, float to = 1) {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX)* (to - from) + from;
}

std::vector<glm::vec3> TreeModel::generateTreesFor1Chunk() {
    srand((unsigned)time(0));
    std::vector<glm::vec3> treeVector;
    for (int i = 0; i < numberOfTrees; i++) {
        treeVector.push_back(glm::vec3(randomFloat(0, chunkSize), 0.0f, randomFloat(0, chunkSize)));
    }

    return treeVector;
}

std::vector<int> TreeModel::populateTreeSeeds() {
    std::vector<int> treeSeed;
    seed += chunkX + chunkZ;
    srand(seed);
    for (int i = 0; i < chunkSize; i++) {
        treeSeed.push_back(rand());
    }
    return treeSeed;
}

