//
// Created by jayohanna on 2020-04-07.
//

#ifndef OPENWORLD_ROCKMODEL_H
#define OPENWORLD_ROCKMODEL_H



#include "Model.h"
#include "../mesh/RockMesh.h"
#include "../texture/Texture.h"

class RockModel : public Model {
public:
    RockModel(std::map<std::string, Shader*> shadersMap, std::map<std::string, Texture*> texturesMap, int chunkX, int chunkZ,
              int chunkSize, std::vector<std::vector<float>> heights, int rockNumber);

    void loadMeshes() override;
    void resetRock();

    std::vector<Vertex> returnRockMeshVertices();

private:
    int chunkX;
    int chunkZ;

    int chunkSize;
    std::vector<std::vector<float>> heights;
    std::vector<Vertex> rockVertices; wa
    int num;
};



#endif //OPENWORLD_ROCKMODEL_H
