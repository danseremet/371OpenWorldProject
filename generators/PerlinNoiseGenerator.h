//
// Created by danseremet on 2020-04-07.
//

#ifndef OPENWORLD_PERLINNOISEGENERATOR_H
#define OPENWORLD_PERLINNOISEGENERATOR_H

#include <random>
#include <iostream>
#include <math.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PerlinNoiseGenerator {
private:
    int seed;
    float roughness;
    int octaves;
    float amplitude;
    std::random_device rd;
    std::mt19937 rng{rd()};
    std::uniform_int_distribution<int> uni{0, 1000000000};

    std::vector<int> p;
public:
    PerlinNoiseGenerator(float roughness, int octaves, float amplitude);

    float getAmplitude() const;

    double noise(double x, double y, double z);

    double fade(double t);

    double grad(int hash, double x, double y, double z);

    double lerp(double t, double a, double b);
};


#endif //OPENWORLD_PERLINNOISEGENERATOR_H
