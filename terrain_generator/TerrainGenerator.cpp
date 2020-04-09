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

TerrainModel *TerrainGenerator::generateTerrain(int terrainSize, int chunkX, int chunkZ) {
    std::vector<std::vector<float>> heights = generateHeights(terrainSize, chunkX, chunkZ);
    std::vector<std::vector<glm::vec3>> colors = colorGenerator->generateColors(heights,
            perlinNoiseGenerator->getAmplitude());

    return new TerrainModel{chunkX, chunkZ, heights, colors, shadersMap, texturesMap};
}

std::vector<std::vector<float>> TerrainGenerator::generateHeights(int terrainSize, int chunkX, int chunkZ) {

    std::vector<std::vector<float>> heights{};

    constexpr double FREQ{40.0f};

    double dx = chunkX * terrainSize;
    double dz = chunkZ * terrainSize;

    std::random_device rd;
    std::mt19937 rng{rd()};
    std::uniform_int_distribution<int> uni{-10, 10};

    for (int z = 0; z < terrainSize + 1; z++) {
        heights.emplace_back();
        for (int x = 0; x < terrainSize + 1; x++) {
            double x_n = (x + dx) / FREQ;
            double y_n = ((x + dx) / FREQ) + ((z + dz) / FREQ);
            double z_n = (z + dz) / FREQ;

            double pn = perlinNoiseGenerator->noise(x_n, y_n, z_n);
            pn *= perlinNoiseGenerator->getAmplitude();
            if (z != 0 && x != 0 && z != terrainSize && x != terrainSize) {
                pn += uni(rng) / 70.0f;
            }
            heights.back().push_back(pn);
        }
    }

    return heights;
}