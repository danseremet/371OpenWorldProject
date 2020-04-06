//
// Created by jayohanna on 2020-04-06.
//

#include "CubeMesh.h"


#include <utility>

using namespace glm;

CubeMesh::CubeMesh(std::map<std::string, Shader*> shadersMap, std::map<std::string, Texture*> texturesMap)
    : Mesh(std::move(shadersMap), std::move(texturesMap)) {
}

void CubeMesh::loadVertices() {
    vec3 RED = vec3(1.0f, 0.0f, 0.0f);
    vertices = {
        // BACK
        {vec3(-0.5f, -0.5f, -0.5f), RED, vec3(0.0f,  0.0f, -1.0f), vec2(0.0f,  0.0f)}, // F
        {vec3(0.5f,  0.5f, -0.5f), RED, vec3(0.0f,  0.0f, -1.0f), vec2(1.0f,  1.0f)},  // B
        {vec3(0.5f, -0.5f, -0.5f), RED, vec3(0.0f,  0.0f, -1.0f), vec2(1.0f,  0.0f)},  // E
        {vec3(0.5f,  0.5f, -0.5f), RED, vec3(0.0f,  0.0f, -1.0f), vec2(1.0f,  1.0f)},  // B
        {vec3(-0.5f, -0.5f, -0.5f), RED, vec3(0.0f,  0.0f, -1.0f), vec2(0.0f,  0.0f)}, // F
        {vec3(-0.5f,  0.5f, -0.5f), RED, vec3(0.0f,  0.0f, -1.0f), vec2(0.0f,  1.0f)}, // C
        // FRONT
        {vec3(-0.5f, -0.5f,  0.5f), RED, vec3(0.0f,  0.0f,  1.0f), vec2(0.0f,  0.0f)}, // G
        {vec3(0.5f, -0.5f,  0.5f), RED, vec3(0.0f,  0.0f,  1.0f), vec2(1.0f,  0.0f)},  // H
        {vec3(0.5f,  0.5f,  0.5f), RED, vec3(0.0f,  0.0f,  1.0f), vec2(1.0f,  1.0f)},  // A
        {vec3(0.5f,  0.5f,  0.5f), RED, vec3(0.0f,  0.0f,  1.0f), vec2(1.0f,  1.0f)},  // A
        {vec3(-0.5f,  0.5f,  0.5f), RED, vec3(0.0f,  0.0f,  1.0f), vec2(0.0f,  1.0f)}, // D
        {vec3(-0.5f, -0.5f,  0.5f), RED, vec3(0.0f,  0.0f,  1.0f), vec2(0.0f,  0.0f)}, // G
        // LEFT
        {vec3(-0.5f,  0.5f,  0.5f), RED, vec3(-1.0f,  0.0f,  0.0f), vec2(1.0f,  0.0f)},// D
        {vec3(-0.5f,  0.5f, -0.5f), RED, vec3(-1.0f,  0.0f,  0.0f), vec2(1.0f,  1.0f)},// C
        {vec3(-0.5f, -0.5f, -0.5f), RED, vec3(-1.0f,  0.0f,  0.0f), vec2(0.0f,  1.0f)},// F
        {vec3(-0.5f, -0.5f, -0.5f), RED, vec3(-1.0f,  0.0f,  0.0f), vec2(0.0f,  1.0f)},// F
        {vec3(-0.5f, -0.5f,  0.5f), RED, vec3(-1.0f,  0.0f,  0.0f), vec2(0.0f,  0.0f)},// G
        {vec3(-0.5f,  0.5f,  0.5f), RED, vec3(-1.0f,  0.0f,  0.0f), vec2(1.0f,  0.0f)},// D
        // RIGHT
        {vec3(0.5f,  0.5f,  0.5f), RED, vec3(1.0f,  0.0f,  0.0f), vec2(1.0f,  0.0f)},  // A
        {vec3(0.5f, -0.5f, -0.5f), RED, vec3(1.0f,  0.0f,  0.0f), vec2(0.0f,  1.0f)},  // E
        {vec3(0.5f,  0.5f, -0.5f), RED, vec3(1.0f,  0.0f,  0.0f), vec2(1.0f,  1.0f)},  // B
        {vec3(0.5f, -0.5f, -0.5f), RED, vec3(1.0f,  0.0f,  0.0f), vec2(0.0f,  1.0f)},  // E
        {vec3(0.5f,  0.5f,  0.5f), RED, vec3(1.0f,  0.0f,  0.0f), vec2(1.0f,  0.0f)},  // A
        {vec3(0.5f, -0.5f,  0.5f), RED, vec3(1.0f,  0.0f,  0.0f), vec2(0.0f,  0.0f)},  // H
        // BOTTOM
        {vec3(-0.5f, -0.5f, -0.5f), RED, vec3(0.0f, -1.0f,  0.0f), vec2(0.0f,  1.0f)}, // F
        {vec3(0.5f, -0.5f, -0.5f), RED, vec3(0.0f, -1.0f,  0.0f), vec2(1.0f,  1.0f)},  // E
        {vec3(0.5f, -0.5f,  0.5f), RED, vec3(0.0f, -1.0f,  0.0f), vec2(1.0f,  0.0f)},  // H
        {vec3(0.5f, -0.5f,  0.5f), RED, vec3(0.0f, -1.0f,  0.0f), vec2(1.0f,  0.0f)},  // H
        {vec3(-0.5f, -0.5f,  0.5f), RED, vec3(0.0f, -1.0f,  0.0f), vec2(0.0f,  0.0f)}, // G
        {vec3(-0.5f, -0.5f, -0.5f), RED, vec3(0.0f, -1.0f,  0.0f), vec2(0.0f,  1.0f)}, // F
        // UP
        {vec3(-0.5f,  0.5f, -0.5f), RED, vec3(0.0f,  1.0f,  0.0f), vec2(0.0f,  1.0f)}, // C
        {vec3(0.5f,  0.5f,  0.5f), RED, vec3(0.0f,  1.0f,  0.0f), vec2(1.0f,  0.0f)},  // A
        {vec3(0.5f,  0.5f, -0.5f), RED, vec3(0.0f,  1.0f,  0.0f), vec2(1.0f,  1.0f)},  // B
        {vec3(0.5f,  0.5f,  0.5f), RED, vec3(0.0f,  1.0f,  0.0f), vec2(1.0f,  0.0f)},  // A
        {vec3(-0.5f,  0.5f, -0.5f), RED, vec3(0.0f,  1.0f,  0.0f), vec2(0.0f,  1.0f)}, // C
        {vec3(-0.5f,  0.5f,  0.5f), RED, vec3(0.0f,  1.0f,  0.0f), vec2(0.0f,  0.0f)}  // D
    };
}

void CubeMesh::draw() {
    mat4 baseplate{ mat4(1.0f) };
    baseplate = translate(baseplate, vec3(0.0f, 3.0f, 0.0f));
    baseplate = scale(baseplate, vec3(6.0f, 6.0f, 6.0f));


    shadersMap["basic"]->use();
    shadersMap["basic"]->setMat4("worldMatrix", baseplate);

    Mesh::draw();
}

void CubeMesh::toggleShowTexture() {
    showTexture = !showTexture;
}
