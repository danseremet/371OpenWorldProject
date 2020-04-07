//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_LEAVES2MODEL_H
#define OPENWORLD_LEAVES2MODEL_H


#include "Mesh.h"

class Leaves2Mesh: public Mesh {

private:
    void loadVertices() override;

    GLboolean showTexture{true};

public:
    Leaves2Mesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap);

    void draw() override;

    void toggleShowTexture();

};



#endif //OPENWORLD_LEAVES2MODEL_H
