//
// Created by Mael Semler on 2020-04-06.
//

#include "TreeModel.h"

#include <utility>
#include <ctime>

int TreeModel::seed = time(0);

TreeModel::TreeModel(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, int chunkX, int chunkZ, int chunkSize, std::vector<std::vector<float>> heights, int numberOfTreesMax, PerlinNoiseGenerator* perlinNoiseGenerator) :
        Model(std::move(shadersMap), std::move(texturesMap)), chunkX(chunkX), chunkZ(chunkZ), chunkSize(chunkSize), heights(heights), numberOfTreesMax(numberOfTreesMax), perlinNoiseGenerator(perlinNoiseGenerator){
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
    std::vector<glm::vec3> treeVector;
    srand(seed * seed + seed);

   
   
    std::vector<std::vector<float>> pnValues{};
    double pn;
    for (int x = 0; x <= chunkSize; x++) {
        pnValues.emplace_back();
        for (int y = 0; y <= chunkSize; y++) {
            pn = perlinNoiseGenerator->noise(x / 800.0f, y / 800.0f, (x / 800.0f + y / 800.0f));
            pnValues.back().push_back(abs(pn));
        }
    }

    int counter = 0;

    while (treeVector.size() < numberOfTreesMax) {
        glm::vec3 tree = glm::vec3(randomFloat(1, chunkSize), 0.0f, randomFloat(1, chunkSize));
        bool overlapping = false;
        float heightOfTree = heights[tree.z][tree.x] / perlinNoiseGenerator->getAmplitude();


        if ( (heightOfTree > -0.25f && heightOfTree < 0.2f) && pnValues[tree.z][tree.x] > 0.05f) {
            for (int j = 0; j < treeVector.size(); j++) {
                glm::vec3 other = treeVector.at(j);
                float dx = abs(tree.x - other.x);
                float dz = abs(tree.z - other.z);
                if (dx < 0.5f || dz < 0.5f) {
                    overlapping = true;
                    break;
                }
            }
            if (!overlapping) {
                counter = 0;
                treeVector.push_back(tree);
            }
        }
        counter++;
        if (counter >= 10 * chunkSize) {
            break;
        }

    }
   
   
    return treeVector;
}

std::vector<int> TreeModel::populateTreeSeeds() {
    std::vector<int> treeSeed;
    seed += chunkX + chunkZ;
    srand(seed);
    for (int i = 0; i < numberOfTreesMax; i++) {
        treeSeed.push_back(rand());
    }
    return treeSeed;
}

