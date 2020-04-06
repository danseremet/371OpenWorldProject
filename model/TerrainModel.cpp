//
// Created by danseremet on 2020-04-04.
//

#include "TerrainModel.h"

#include <utility>

TerrainModel::TerrainModel(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap) :
        Model(std::move(shadersMap), std::move(texturesMap)) {
}

void TerrainModel::loadMeshes() {
    auto *bMesh = new TerrainMesh{shadersMap, texturesMap};
    bMesh->loadMesh();
    meshes.push_back(bMesh);
}
