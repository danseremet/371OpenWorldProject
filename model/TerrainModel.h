//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_TERRAINMODEL_H
#define OPENWORLD_TERRAINMODEL_H



#include "Model.h"
#include "../mesh/TerrainMesh.h"
#include "../texture/Texture.h"

class TerrainModel: public Model {
private:
    std::vector<std::vector<float>> heights;

    std::vector<std::vector<glm::vec3>> colors;

    int chunkX;
    int chunkZ;
public:
    TerrainModel(int chunkX, int chunkZ, std::vector<std::vector<float>> heights, std::vector<std::vector<glm::vec3>> colors,
            std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap);

    const std::vector<std::vector<float>> getHeights() const;

    void loadMeshes() override;
};



#endif //OPENWORLD_TERRAINMODEL_H
