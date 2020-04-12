//
// Created by Mael Semler on 2020-04-06.
//

#ifndef OPENWORLD_TREEMODEL_H
#define OPENWORLD_TREEMODEL_H



#include "Model.h"
#include "../mesh/BranchMesh.h"
#include "../mesh/LeavesMesh.h"
#include "../mesh/Leaves2Mesh.h"
#include "../texture/Texture.h"
#include "../generators/PerlinNoiseGenerator.h"

class TreeModel: public Model {
public:
    TreeModel(std::map<std::string, Shader*> shadersMap, std::map<std::string, Texture*> texturesMap, int chunkX, int chunkZ, int chunkSize, std::vector<std::vector<float>> heights, int numberOfTreesMax, PerlinNoiseGenerator* perlinNoiseGenerator);

    void loadMeshes() override;

    void setTreeNumber();

private:
    std::vector<std::vector<float>> heights;
    
    static int seed;

    PerlinNoiseGenerator* perlinNoiseGenerator;

    int numberOfTreesMax;

    int chunkX;

    int chunkZ;

    int chunkSize;

    std::vector<glm::vec3> generateTreesFor1Chunk();

    float randomFloat(float from, float to);

    std::vector<int> populateTreeSeeds();

};



#endif //OPENWORLD_TREEMODEL_H
