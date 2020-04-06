//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_TERRAINMODEL_H
#define OPENWORLD_TERRAINMODEL_H



#include "Model.h"
#include "../mesh/TerrainMesh.h"
#include "../texture/Texture.h"

class TerrainModel: public Model {
public:
    TerrainModel(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap);

    void loadMeshes() override;
};



#endif //OPENWORLD_TERRAINMODEL_H
