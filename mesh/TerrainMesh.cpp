//
// Created by danseremet on 2020-04-04.
//

#include "TerrainMesh.h"


#include <utility>

using namespace glm;

TerrainMesh::TerrainMesh(std::vector<std::vector<float>> heights, std::vector<std::vector<glm::vec3>> colors,
                         std::map<std::string, Shader *> shadersMap, std::map<std::string, Texture *> texturesMap)
        : Mesh(std::move(shadersMap), std::move(texturesMap)), heights(std::move(heights)), colors(std::move(colors)) {
}

void TerrainMesh::loadVertices() {
//    std::cout << "PERLIN NOISE\n";
// Dont remove (for debugging)
//    for (int i = 0; i < heights.size(); i++) {
//        for (int j = 0; j < heights.size(); j++) {
//            std::cout << heights[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << "END\n";
//    for (int z = 0; z < heights.size(); z++) {
//        for (int x = 0; x < heights.size(); x++) {
//            std::cout << '(' << colors[z][x].x << ", " << colors[z][x].y << ", " << colors[z][x].z << ") ";
//        }
//        std::cout << std::endl;
//    }

    // TODO use a chunk int row int col index to offset x and z

    int lastIndex = heights.size() - 1;

    for (int z{0}; z < lastIndex; z += 2) {

        for (int x{0}; x < lastIndex; x += 2) {

//            std::cout << "(x=" << x << ", y=" << heights[z][x] << ", z=" << z << ") ";

            // 9 position vertices based on height
            std::vector<vec3> positions{};
            positions.push_back({x, heights[z][x], z});
            positions.push_back({x + 1, heights[z][x + 1], z});
            positions.push_back({x + 2, heights[z][x + 2], z});

            positions.push_back({x, heights[z + 1][x], z + 1});
            positions.push_back({x + 1, heights[z + 1][x + 1], z + 1});
            positions.push_back({x + 2, heights[z + 1][x + 2], z + 1});

            positions.push_back({x, heights[z + 2][x], z + 2});
            positions.push_back({x + 1, heights[z + 2][x + 1], z + 2});
            positions.push_back({x + 2, heights[z + 2][x + 2], z + 2});


            // 6 colors for the 8 triangles
            std::vector<vec3> orderedColors{};
            // 0  1 1  2
            // 3  4 4  5
            orderedColors.push_back({colors[z][x]});            // 0
            orderedColors.push_back({colors[z][x + 1]});        // 1
            orderedColors.push_back({colors[z][x + 1]});        // 1
            orderedColors.push_back({colors[z][x + 2]});        // 2
            orderedColors.push_back({colors[z + 1][x]});        // 3
            orderedColors.push_back({colors[z + 1][x + 1]});    // 4
            orderedColors.push_back({colors[z + 1][x + 1]});    // 4
            orderedColors.push_back({colors[z + 1][x + 2]});    // 5

            // 24 ordered indices for drawing 8 triangles
            std::vector<int> indices = {
                    0, 3, 4,
                    0, 4, 1,
                    1, 4, 2,
                    4, 5, 2,
                    3, 6, 4,
                    6, 7, 4,
                    4, 7, 8,
                    4, 8, 5,
            };

            // 8 ordered normals for 8 triangles
            std::vector<vec3> orderedNormals{};
            for (int i{0}; i < indices.size(); i += 3) {
                vec3 normal = glm::triangleNormal(positions[i], positions[i + 1], positions[i + 2]);
                orderedNormals.push_back(normal);
            }

            // 24 ordered positions for the 8 vertices
            std::vector<vec3> orderedPositions{};
            for (auto i : indices) {
                orderedPositions.push_back(positions[i]);
            }

            // For every 3 of each data combine into a Vertex in order
            for (int i{0}; i < indices.size(); i += 3) {

                Vertex v0 = {orderedPositions[i], orderedColors[i / 3], orderedNormals[i / 3]};
                Vertex v1 = {orderedPositions[i + 1], orderedColors[i / 3], orderedNormals[i / 3]};
                Vertex v2 = {orderedPositions[i + 2], orderedColors[i / 3], orderedNormals[i / 3]};

                vertices.push_back(v0);
                vertices.push_back(v1);
                vertices.push_back(v2);
            }
        }
    }

}

void TerrainMesh::setupVertices() { // cube mesh
    // vao
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // vertex vbo
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) nullptr);
    glEnableVertexAttribArray(0);
    // vertex color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) sizeof(glm::vec3));
    glEnableVertexAttribArray(1);
    // vertex normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (2 * sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);


    glBindVertexArray(0);
}

void TerrainMesh::draw() {
    shadersMap["terrain"]->use();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void TerrainMesh::toggleShowTexture() {
    showTexture = !showTexture;
}
