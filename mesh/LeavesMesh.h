//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_LEAVESMODEL_H
#define OPENWORLD_LEAVESMODEL_H


#include "Mesh.h"

class LeavesMesh: public Mesh {

private:
    void loadVertices() override;

    GLboolean showTexture{true};

public:
    LeavesMesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap);

    void draw() override;

    void toggleShowTexture();
};



#endif //OPENWORLD_LEAVESMODEL_H
