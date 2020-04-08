//
//Created by Mael Semler on 2020-04-06.
//

#ifndef OPENWORLD_LEAVES2MODEL_H
#define OPENWORLD_LEAVES2MODEL_H


#include "Mesh.h"

class Leaves2Mesh: public Mesh {

private:
    void loadVertices() override;

    void loadTransforms() override;

    std::vector<glm::mat4> modelMatrices;

    GLboolean showTexture{true};

    std::vector<glm::vec3> allPositions;

    float leavesSize;

    float size;

    int numberOfLeaves;

    float angleTree;

    std::vector<std::vector<float>> heights;

public:
    Leaves2Mesh(std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap, std::vector<int>  tSeed, std::vector<glm::vec3> positions, std::vector<std::vector<float>> heights);

    std::vector<int>  seed;

    void draw() override;

    void toggleShowTexture();

};



#endif //OPENWORLD_LEAVES2MODEL_H
