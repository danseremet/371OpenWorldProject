//
//Created by Mael Semler on 2020-04-06.
//

#ifndef OPENWORLD_LEAVES2MODEL_H
#define OPENWORLD_LEAVES2MODEL_H


#include "Mesh.h"

class Leaves2Mesh: public Mesh {

private:
    void loadVertices() override;

    GLboolean showTexture{true};

    std::vector<glm::vec3> allPositions;

public:
    Leaves2Mesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, std::vector<int>  tSeed, std::vector<glm::vec3> positions);

    std::vector<int>  seed;

    void draw() override;

    void toggleShowTexture();

};



#endif //OPENWORLD_LEAVES2MODEL_H
