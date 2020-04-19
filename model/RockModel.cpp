//
// Created by jayohanna on 2020-04-07.
//

#include "RockModel.h"

#include <utility>
#include <ctime>

using namespace glm;

RockModel::RockModel(std::map<std::string, Shader*> shadersMap, std::map<std::string, Texture*> texturesMap, int chunkX, int chunkZ, int chunkSize, std::vector<std::vector<float>> heights, int rockNumber) :
    Model(std::move(shadersMap), std::move(texturesMap)), chunkX(chunkX), chunkZ(chunkZ), chunkSize(chunkSize), heights(heights), num(rockNumber) {
}

void RockModel::loadMeshes() {
    for (int i = 0; i < num; i++)
    {
        auto* rockMesh = new RockMesh{ shadersMap, texturesMap, chunkX, chunkZ, chunkSize, heights };
        rockMesh->loadMesh();
        meshes.push_back(rockMesh);
    }
}

void RockModel::resetRock() {
    meshes.clear();
    loadMeshes();
}

std::vector<Vertex> RockModel::returnRockMeshVertices() {
    return rockVertices;
}