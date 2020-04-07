//
// Created by jayohanna on 2020-04-06.
//

#include "CubeModel.h"

#include <utility>

using namespace glm;

CubeModel::CubeModel(std::map<std::string, Shader*> shadersMap, std::map<std::string, Texture*> texturesMap) :
    Model(std::move(shadersMap), std::move(texturesMap)) {
}

void CubeModel::loadMeshes() {
    auto* cMesh = new CubeMesh{ shadersMap, texturesMap };
    cMesh->loadMesh();
    meshes.push_back(cMesh);
}
