//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_TERRAINMESH_H
#define OPENWORLD_TERRAINMESH_H


#include "Mesh.h"

class TerrainMesh: public Mesh {

private:
    void loadVertices() override;

    GLboolean showTexture{true};

public:
    TerrainMesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap);

    void draw() override;

    void toggleShowTexture();
};



#endif //OPENWORLD_TERRAINMESH_H
