//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_BRANCHMESH_H
#define OPENWORLD_BRANCHMESH_H


#include "Mesh.h"

class BranchMesh: public Mesh {

private:
    void loadVertices() override;

    GLboolean showTexture{true};

public:
    BranchMesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap);

    void draw() override;

    void toggleShowTexture();
};



#endif //OPENWORLD_BRANCHMESH_H
