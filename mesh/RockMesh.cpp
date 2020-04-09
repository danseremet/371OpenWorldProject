//
// Created by jayohanna on 2020-04-07.
//

#include "RockMesh.h"


#include <utility>
#include <ctime>

using namespace glm;

int RockMesh::seed = time(0);

RockMesh::RockMesh(std::map<std::string, Shader*> shadersMap, std::map<std::string, Texture*> texturesMap,
        int chunkX, int chunkZ, int chunkSize, std::vector<std::vector<float>> heights)
    : Mesh(std::move(shadersMap), std::move(texturesMap)), chunkX(chunkX), chunkZ(chunkZ),
    chunkSize(chunkSize), heights(heights) {
}


std::vector<vec3> RockMesh::generateVertices() {
    std::vector<vec3> rockVertices = {};
    randomizeVertices();
    rockVertices.push_back({ -n, o, m });
    randomizeVertices();
    rockVertices.push_back({ n, o, m });
    randomizeVertices();
    rockVertices.push_back({ -n, o, -m });
    randomizeVertices();
    rockVertices.push_back({ n, o, -m });
    randomizeVertices();
    rockVertices.push_back({ o, m, n });
    randomizeVertices();
    rockVertices.push_back({ o, m, -n });
    randomizeVertices();
    rockVertices.push_back({ o, -m, n });
    randomizeVertices();
    rockVertices.push_back({ o, -m, -n });
    randomizeVertices();
    rockVertices.push_back({ m, n, o });
    randomizeVertices();
    rockVertices.push_back({ -m, n, o });
    randomizeVertices();
    rockVertices.push_back({ m, -n, o });
    randomizeVertices();
    rockVertices.push_back({ -m, -n, o });

    return rockVertices;
}

vec3 RockMesh::normal(vec3 a, vec3 b, vec3 c) {
    vec3 vec1 = a - b;
    vec3 vec2 = b - c;
    return cross(vec1, vec2);
}

void RockMesh::setRandomSeed() {
    seed += chunkX + chunkZ;
    srand(seed);
}

float RockMesh::randomFloat(float from = 0, float to = 1) {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * (to - from) + from;
}

void RockMesh::randomizeVertices() {
    setRandomSeed();
    int option = rand() % 3;
    float r;

    if (option)
    {
        r = randomFloat(0, 0.2);
        m += r;
    }
    else
    {
        r = randomFloat(0, 0.07);
        m -= r;
    }

    setRandomSeed();
    option = rand() % 3;
    if (option)
    {
        r = randomFloat(0, 0.2);
        n += r;
    }
    else
    {
        r = randomFloat(0, 0.07);
        n -= r;
    }

    setRandomSeed();
    option = rand() % 3;
    if (option)
    {
        r = randomFloat(0, 0.2);
        o += r;
    }
    else
    {
        r = randomFloat(0, 0.07);
        o -= r;
    }
}

void RockMesh::loadVertices() {
    Vertex vertex;
    vec3 GREY = vec3(0.8f, 0.8f, 0.8f);

    std::vector<vec3> rockVertices = generateVertices();

    std::vector<vec3> triangles = {
        rockVertices[1],
        rockVertices[4],
        rockVertices[0],

        rockVertices[4],
        rockVertices[9],
        rockVertices[0],

        rockVertices[4],
        rockVertices[5],
        rockVertices[9],

        rockVertices[8],
        rockVertices[5],
        rockVertices[4],

        rockVertices[1],
        rockVertices[8],
        rockVertices[4],

        rockVertices[1],
        rockVertices[10],
        rockVertices[8],

        rockVertices[10],
        rockVertices[3],
        rockVertices[8],

        rockVertices[8],
        rockVertices[3],
        rockVertices[5],

        rockVertices[3],
        rockVertices[2],
        rockVertices[5],

        rockVertices[3],
        rockVertices[7],
        rockVertices[2],

        rockVertices[3],
        rockVertices[10],
        rockVertices[7],

        rockVertices[10],
        rockVertices[6],
        rockVertices[7],

        rockVertices[6],
        rockVertices[11],
        rockVertices[7],

        rockVertices[6],
        rockVertices[0],
        rockVertices[11],

        rockVertices[6],
        rockVertices[1],
        rockVertices[0],

        rockVertices[10],
        rockVertices[1],
        rockVertices[6],

        rockVertices[11],
        rockVertices[0],
        rockVertices[9],

        rockVertices[2],
        rockVertices[11],
        rockVertices[9],

        rockVertices[5],
        rockVertices[2],
        rockVertices[9],

        rockVertices[11],
        rockVertices[2],
        rockVertices[7],
    };

    for (int i = 0; i < triangles.size(); i += 3)
    {
        vec3 norm = normal(triangles[i], triangles[i + 1], triangles[i + 2]);
        vertex = { triangles[i], GREY, norm };
        vertices.push_back(vertex);
        vertex = { triangles[i + 1], GREY, norm };
        vertices.push_back(vertex);
        vertex = { triangles[i + 2], GREY, norm };
        vertices.push_back(vertex);
    }
}

void RockMesh::draw() {
    shadersMap["basic"]->use();
    shadersMap["basic"]->setMat4("worldMatrix", baseplate);

    Mesh::draw();
}

void RockMesh::toggleShowTexture() {
    showTexture = !showTexture;
}

void RockMesh::loadTransforms() {
    baseplate = mat4(1.0f);

    float scaleX = randomFloat(0.25f, 1.25f);
    float scaleY = randomFloat(0.25f, 1.25f);
    float scaleZ = randomFloat(0.25f, 1.25f);

    int dx = chunkSize * chunkX;
    int dz = chunkSize * chunkZ;
    float translationX = randomFloat(0, chunkSize);
    float translationZ = randomFloat(0, chunkSize);
    float translationY = heights[translationZ][translationX];

    baseplate = translate(baseplate, vec3(translationX + dx, translationY, translationZ + dz));
    baseplate = scale(baseplate, vec3(scaleX, scaleY, scaleZ));
}