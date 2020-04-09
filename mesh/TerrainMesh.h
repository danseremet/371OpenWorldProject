//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_TERRAINMESH_H
#define OPENWORLD_TERRAINMESH_H


#include "Mesh.h"

class TerrainMesh : public Mesh {

private:
    void loadVertices() override;

    void setupVertices() override;

    GLboolean showTexture{true};

    std::vector<std::vector<float>> heights;

    std::vector<std::vector<glm::vec3>> colors;

    int chunkX;
    int chunkZ;

    glm::vec3 normal(glm::vec3 a, glm::vec3 b, glm::vec3 c);
public:
    TerrainMesh(int chunkX, int chunkZ, std::vector<std::vector<float>> heights, std::vector<std::vector<glm::vec3>> colors,
                std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap);

    void draw() override;

    void toggleShowTexture();
};


#endif //OPENWORLD_TERRAINMESH_H
