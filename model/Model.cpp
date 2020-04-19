  //
// Created by danseremet on 2020-04-04.
//

#include <map>
#include <utility>
#include "Model.h"

Model::Model(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap) :
        shadersMap{std::move(shadersMap)}, texturesMap{std::move(texturesMap)} {
}

void Model::loadModel() {
    loadMeshes();
}

void Model::draw() {
    for (GLuint i{0}; i < meshes.size(); i++) {
        meshes[i]->draw(); 
    }
}

void Model::loadMeshes() {
    std::cout << "loadMeshes cube\n";
    auto *mesh = new Mesh{shadersMap, texturesMap};
    meshes.push_back(mesh);
}
