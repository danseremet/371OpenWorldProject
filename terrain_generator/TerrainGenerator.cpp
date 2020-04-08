//
// Created by danseremet on 2020-04-07.
//

#include "TerrainGenerator.h"

/**
 * Adapted with the help of https://github.com/TheThinMatrix/LowPolyTerrain from the public domain.
 */
TerrainGenerator::TerrainGenerator(PerlinNoiseGenerator *perlinNoiseGenerator, ColorGenerator *colorGenerator,
                                   std::map<std::string, Shader *> shadersMap,
                                   std::map<std::string, Texture *> texturesMap) :
        perlinNoiseGenerator(perlinNoiseGenerator), colorGenerator(colorGenerator), shadersMap{std::move(shadersMap)},
        texturesMap{std::move(texturesMap)} {
}

TerrainModel *TerrainGenerator::generateTerrain(int terrainSize) {
    std::vector<std::vector<float>> heights = generateHeights(terrainSize);
    std::vector<std::vector<glm::vec3>> colors = colorGenerator->generateColors(heights,
            perlinNoiseGenerator->getAmplitude());

    return new TerrainModel{heights, colors, shadersMap, texturesMap};
}

std::vector<std::vector<float>> TerrainGenerator::generateHeights(int terrainSize) {

    std::vector<std::vector<float>> heights{};

    constexpr double FREQ{40.0f};
    constexpr int AMPLITUDE{10};

    for (int z = 0; z < terrainSize + 1; z++) {
        heights.emplace_back();
        for (int x = 0; x < terrainSize + 1; x++) {
            double pn2 = perlinNoiseGenerator->noise(x / FREQ, x / FREQ + z / FREQ, z / FREQ);
            pn2 *= AMPLITUDE;
            heights.back().push_back(pn2);
        }
    }

    return heights;
}