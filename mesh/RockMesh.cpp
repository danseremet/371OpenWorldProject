//
// Created by jayohanna on 2020-04-07.
//

#include "RockMesh.h"


#include <utility>
#include <ctime>

using namespace glm;

RockMesh::RockMesh(std::map<std::string, Shader*> shadersMap, std::map<std::string, Texture*> texturesMap)
    : Mesh(std::move(shadersMap), std::move(texturesMap)) {
}


std::vector<vec3> RockMesh::generateVertices() {
    std::vector<vec3> rockVertices = {};
    randomize();
    rockVertices.push_back({ -n, o, m });
    randomize();
    rockVertices.push_back({ n, o, m });
    randomize();
    rockVertices.push_back({ -n, o, -m });
    randomize();
    rockVertices.push_back({ n, o, -m });
    randomize();
    rockVertices.push_back({ o, m, n });
    randomize();
    rockVertices.push_back({ o, m, -n });
    randomize();
    rockVertices.push_back({ o, -m, n });
    randomize();
    rockVertices.push_back({ o, -m, -n });
    randomize();
    rockVertices.push_back({ m, n, o });
    randomize();
    rockVertices.push_back({ -m, n, o });
    randomize();
    rockVertices.push_back({ m, -n, o });
    randomize();
    rockVertices.push_back({ -m, -n, o });

    return rockVertices;
}

vec3 RockMesh::normal(vec3 a, vec3 b, vec3 c) {
    vec3 vec1 = a - b;
    vec3 vec2 = b - c;
    return cross(vec1, vec2);
}

void RockMesh::randomize() {
    srand(time(0)+rand());
    int option = rand() % 3;
    float r;

    if (option)
    {
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX * 5);
        m += r;
    }
    else
    {
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX * 15);
        m -= r;
    }

    srand(time(0) + rand());
    option = rand() % 3;
    if (option)
    {
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX * 5);
        n += r;
    }
    else
    {
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX * 15);
        n -= r;
    }

    srand(time(0) + rand());
    option = rand() % 3;
    if (option)
    {
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX * 5);
        o += r;
    }
    else
    {
        r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX * 15);
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
    //mat4 baseplate{ mat4(1.0f) };
    //baseplate = translate(baseplate, vec3(8.0f, 0.5f, 8.0f));
    //baseplate = scale(baseplate, vec3(1.0f, 1.0f, 1.0f));


    shadersMap["basic"]->use();
    shadersMap["basic"]->setMat4("worldMatrix", baseplate);

    Mesh::draw();
}

void RockMesh::toggleShowTexture() {
    showTexture = !showTexture;
}

void RockMesh::loadTransforms() {
    baseplate = mat4(1.0f);

    float scaleX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + 0.25f;
    float scaleY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + 0.25f;
    float scaleZ = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) + 0.25f;

    float translationX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 10;
    float translationZ = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 10;

    baseplate = translate(baseplate, vec3(translationX, 0.5f, translationZ));
    baseplate = scale(baseplate, vec3(scaleX, scaleY, scaleZ));

    shadersMap["basic"]->use();
    shadersMap["basic"]->setMat4("worldMatrix", baseplate);
}