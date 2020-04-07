//
// Created by jayohanna on 2020-04-06.
//

#ifndef OPENWORLD_CUBEMESH_H
#define OPENWORLD_CUBEMESH_H


#include "Mesh.h"

class CubeMesh : public Mesh {

private:
    void loadVertices() override;

    GLboolean showTexture{ true };

public:
    CubeMesh(std::map<std::string, Shader*> shadersMap, std::map<std::string, Texture*> texturesMap);

    void draw() override;

    void toggleShowTexture();
};



#endif //OPENWORLD_CUBEMESH_H
