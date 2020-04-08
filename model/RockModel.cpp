//
// Created by jayohanna on 2020-04-07.
//

#include "RockModel.h"

#include <utility>
#include <ctime>

using namespace glm;

RockModel::RockModel(std::map<std::string, Shader*> shadersMap, std::map<std::string, Texture*> texturesMap) :
    Model(std::move(shadersMap), std::move(texturesMap)) {
}

void RockModel::loadMeshes() {
    for (int i = 0; i < 5; i++)
    {
        auto* rockMesh = new RockMesh{ shadersMap, texturesMap };
        rockMesh->loadMesh();
        meshes.push_back(rockMesh);
    }
}

void RockModel::resetRock() {
    meshes.clear();
    loadMeshes();
}