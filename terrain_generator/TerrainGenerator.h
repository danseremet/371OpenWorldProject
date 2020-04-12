//
// Created by danseremet on 2020-04-07.
//

#ifndef OPENWORLD_TERRAINGENERATOR_H
#define OPENWORLD_TERRAINGENERATOR_H

#define GLEW_STATIC 1 // necessary for glew

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <limits>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../generators/PerlinNoiseGenerator.h"
#include "../generators/ColorGenerator.h"
#include "../shader/Shader.h"
#include "../texture/Texture.h"
#include "../model/TerrainModel.h"

class TerrainGenerator {
private:
    PerlinNoiseGenerator *perlinNoiseGenerator;
    ColorGenerator *colorGenerator;

    std::map<std::string, Shader *> shadersMap;
    std::map<std::string, Texture *> texturesMap;
public:
    TerrainGenerator(PerlinNoiseGenerator *perlinNoiseGenerator, ColorGenerator *colorGenerator, std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap);

    TerrainModel *generateTerrain(int terrainSize, int chunkX, int chunkZ);

    std::vector<std::vector<float>> generateHeights(int terrainSize, int chunkX, int chunkZ);
};


#endif //OPENWORLD_TERRAINGENERATOR_H
