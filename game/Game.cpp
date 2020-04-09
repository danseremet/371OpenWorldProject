//
// Created by danseremet on 2020-04-04.
//

#include "Game.h"
#include "../keyboard/Keyboard.h"


using namespace glm;
using namespace std;


Game::Game() {

    // Window setup
    window = WindowManager::getWindow();
    // Camera setup
    camera = new Camera{};

    // Shader loading
    shadersMap = std::map<std::string, Shader*>{};
    shadersMap["basic"] = new Shader{"basic"};

    // Setup P & V matrix properties
    fovy = 70.0f;
    scrWidth = WindowManager::getDefaultScreenWidth();
    scrHeight = WindowManager::getDefaultScreenHeight();
    aspect = computeAspectRatio();
    zNear = 0.01f;
    zFar = 3000.0f;     // careful
    projectionMatrix = createProjectionMatrix();
    viewMatrix = camera->getViewMatrix();

    // Generate Terrain
    int octaves{3}; // unused
    float amplitude{100.0f}; // USED
    float roughness{0.35f}; // unused
    auto * perlinNoiseGenerator = new PerlinNoiseGenerator(roughness, octaves, amplitude);
    auto * colorGenerator = new ColorGenerator(0.55f);
    terrainGenerator = new TerrainGenerator(perlinNoiseGenerator, colorGenerator, shadersMap, texturesMap);

    // Model creation
    int chunkSize{200};
    int numberOfChunks{4}; // careful N*2 memory
    int numberOfRocks = 0.15 * chunkSize;
    int numberOfTrees = 2.0 * chunkSize;

    for (int z{0}; z < numberOfChunks; z++) {
        terrain.insert(make_pair(z, map<int, Model*>()));
        rocks.insert(make_pair(z, map<int, Model*>()));
        trees.insert(make_pair(z, map<int, Model*>()));

        for (int x{0}; x < numberOfChunks; x++) {

            Model* terrainModel = terrainGenerator->generateTerrain(chunkSize, x, z);
            terrainModel->loadModel();
            terrain[z].insert(make_pair(x, terrainModel));

            auto heights = ((TerrainModel *) terrainModel)->getHeights();

            Model* rockModel= new RockModel{ shadersMap, texturesMap, x, z, chunkSize, heights, numberOfRocks };
            rockModel->loadModel();
            rocks[z].insert(make_pair(x, rockModel));

            Model* treeModel = new TreeModel{ shadersMap, texturesMap, x, z, chunkSize, heights, numberOfTrees, perlinNoiseGenerator }; // Call the treeModel
            treeModel->loadModel();
            trees[z].insert(make_pair(x, treeModel));
        }
    }

    // For frame time
    dt = 0.0f;
    lastFrameTime = glfwGetTime();

    // Mouse positions
    glfwGetCursorPos(window, &lastMousePosX, &lastMousePosY);

    // OpenGL settings
    glEnable(GL_CULL_FACE); // hiden surface removal
    glEnable(GL_DEPTH_TEST);
    polygonMode = GL_FILL;
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
}

void Game::launch() {
    while (!glfwWindowShouldClose(window)) {
        gameLoop();
    }
}


Game::~Game() {
    // Shutdown GLFW
    glfwTerminate();
}

void Game::gameLoop() {
    frameSetup();
    drawModels();
    frameEnd();
}

void Game::frameSetup() {
    // Frame duration
    dt = static_cast<float>(glfwGetTime()) - lastFrameTime;
    lastFrameTime += dt;
    glClearColor(0.02f, 0.602f, 0.953f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setupBasicShader();
}

void Game::drawModels() {
    map<int, map<int, Model*>>::iterator itr;
    map<int, Model*>::iterator ptr;
    for (itr = terrain.begin(); itr != terrain.end(); itr++) {
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
            ptr->second->draw();
        }
    }
    for (itr = rocks.begin(); itr != rocks.end(); itr++) {
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
            ptr->second->draw();
        }
    }
    for (itr = trees.begin(); itr != trees.end(); itr++) {
        for (ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
            ptr->second->draw();
        }
    }
}

void Game::frameEnd() {
    glfwSwapBuffers(window);            // Double buffering
    glfwPollEvents();                    // Detect IO events
    Keyboard::processInput(this);   // Process inputs
}

GLFWwindow *Game::getWindow() const {
    return window;
}

Camera *Game::getCamera() const {
    return camera;
}

Shader *Game::getShader() const {
    return shader;
}

GLfloat Game::getFovy() const {
    return fovy;
}

void Game::setFovy(GLfloat newFovy) {
    this->fovy = newFovy;
}

glm::mat4 Game::createProjectionMatrix() {
    return glm::perspective(fovy, aspect, zNear, zFar);
}


void Game::updateProjectionMatrix() {
    projectionMatrix = createProjectionMatrix();
    shader->setMat4("projectionMatrix", projectionMatrix);
}

GLuint Game::getScrWidth() const {
    return scrWidth;
}

GLuint Game::getScrHeight() const {
    return scrHeight;
}

void Game::setScrWidth(GLuint newScrWidth) {
    this->scrWidth = newScrWidth;
}

void Game::setScrHeight(GLuint newScrHeight) {
    this->scrHeight = newScrHeight;
}

void Game::updateAspectRatio() {
    this->aspect = computeAspectRatio();
}

GLfloat Game::computeAspectRatio() {
    return scrWidth * 1.0f / scrHeight * 1.0f;;
}

void Game::setupBasicShader() {
    shadersMap["basic"]->use();
    shadersMap["basic"]->setMat4("projectionMatrix", projectionMatrix);
    viewMatrix = camera->getViewMatrix();
    shadersMap["basic"]->setMat4("viewMatrix", viewMatrix);
    shadersMap["basic"]->setVec3("viewPos", camera->cameraPosition);
}

const map<int, std::map<int, Model *>> &Game::getRocks() const {
    return rocks;
}

