//
// Created by jayohanna on 2020-04-07.
//

#ifndef OPENWORLD_ROCKMESH_H
#define OPENWORLD_ROCKMESH_H


#include "Mesh.h"

class RockMesh : public Mesh {

private:
    void loadVertices() override;
    void loadTransforms() override;
    std::vector<glm::vec3> generateVertices();
    glm::vec3 normal(glm::vec3 a, glm::vec3 b, glm::vec3 c);
    void setRandomSeed();
    void randomizeVertices();
    float randomFloat(float from, float to);

    GLboolean showTexture{ true };

    glm::vec2 chunkPosition;

    glm::mat4 baseplate{ glm::mat4(1.0f) };

    std::vector<std::vector<float>> heights;

    float m = 0.851f;
    float n = 0.526f;
    float o = 0.0f;

public:
    RockMesh(std::map<std::string, Shader*> shadersMap, std::map<std::string, Texture*> texturesMap, glm::vec2 chunkPosition, std::vector<std::vector<float>> heights);

    void draw() override;

    void toggleShowTexture();
};



#endif //OPENWORLD_ROCKMESH_H
