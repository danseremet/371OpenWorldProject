//
// Created by jayohanna on 2020-04-07.
//

#include "RockModel.h"

#include <utility>
#include <ctime>

using namespace glm;

RockModel::RockModel(std::map<std::string, Shader*> shadersMap, std::map<std::string, Texture*> texturesMap, glm::vec2 chunkPosition, std::vector<std::vector<float>> heights, int rockNumber) :
    Model(std::move(shadersMap), std::move(texturesMap)), chunkPosition(chunkPosition), heights(heights), num(rockNumber) {
}

void RockModel::loadMeshes() {
    for (int i = 0; i < num; i++)
    {
        auto* rockMesh = new RockMesh{ shadersMap, texturesMap, chunkPosition, heights };
        rockMesh->loadMesh();
        meshes.push_back(rockMesh);
    }
}

void RockModel::resetRock() {
    meshes.clear();
    loadMeshes();
}