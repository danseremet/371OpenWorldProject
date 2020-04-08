//
// Created by danseremet on 2020-04-07.
//

#include "ColorGenerator.h"

/**
 * Adapted with the help of https://github.com/TheThinMatrix/LowPolyTerrain from the public domain.
 */
ColorGenerator::ColorGenerator(float spread) : spread(spread), halfSpread(spread / 2.0f) {

    glm::vec3 c1{0.648f, 0.598f, 0.445f}; // yellow
    glm::vec3 c2{0.316f, 0.543f, 0.125f}; // light green
    glm::vec3 c3{0.297f, 0.492f, 0.254f}; // normal green
    glm::vec3 c4{0.471f, 0.471f, 0.471f}; // grey
    glm::vec3 c5{0.784f, 0.784f, 0.824f}; // light grey
    biomeColors = {c1, c2, c3, c4, c5};
    this->halfSpread = spread / 2.0f;
    this->part = 1.0f / (biomeColors.size() - 1.0f);
}

std::vector<std::vector<glm::vec3>>
ColorGenerator::generateColors(std::vector<std::vector<float>> heights, float amplitude) {

    std::vector<std::vector<glm::vec3>> colors{};

    for (int z = 0; z < heights.size(); z++) {
        colors.emplace_back();
        for (int x = 0; x < heights.size(); x++) {
            float h = heights[z][x];
            glm::vec3 color = calculateColor(h, amplitude);
            colors.back().push_back(color);
        }
    }


    return colors;
}

glm::vec3 ColorGenerator::calculateColor(float height, float amplitude) {
    float value = (height + amplitude) / (amplitude * 2);
    value = glm::clamp((value - halfSpread) * (1.0f / spread), 0.0f, 0.9999f);
    int firstBiome = glm::floor(value / part);
    float blend = (value - (firstBiome * part)) / part;
    return glm::mix(biomeColors[firstBiome], biomeColors[firstBiome + 1], blend);
}
