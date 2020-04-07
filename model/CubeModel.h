//
// Created by jayohanna on 2020-04-06.
//

#ifndef OPENWORLD_CUBEMODEL_H
#define OPENWORLD_CUBEMODEL_H



#include "Model.h"
#include "../mesh/CubeMesh.h"
#include "../texture/Texture.h"

class CubeModel : public Model {
public:
    CubeModel(std::map<std::string, Shader*> shadersMap, std::map<std::string, Texture*> texturesMap);

    void loadMeshes() override;
};



#endif //OPENWORLD_CUBEMODEL_H
