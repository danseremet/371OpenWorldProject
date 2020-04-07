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
    shadersMap["terrain"] = new Shader{"terrain"};

    // Setup P & V matrix properties
    fovy = 70.0f;
    scrWidth = WindowManager::getDefaultScreenWidth();
    scrHeight = WindowManager::getDefaultScreenHeight();
    aspect = computeAspectRatio();
    zNear = 0.01f;
    zFar = 100.0f;
    projectionMatrix = createProjectionMatrix();
    viewMatrix = camera->getViewMatrix();

    // Model creation
    terrainModel = new TerrainModel{shadersMap, texturesMap};
    terrainModel->loadModel();
    cubeModel = new CubeModel{ shadersMap, texturesMap };
    cubeModel->loadModel();

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
    glClearColor(0.2f, 0.4f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setupBasicShader();
    setupTerrainShader();
}

void Game::drawModels() {
    terrainModel->draw();
    cubeModel->draw();
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

void Game::setupTerrainShader() {
    shadersMap["terrain"]->use();
    shadersMap["terrain"]->setMat4("projectionMatrix", projectionMatrix);
    viewMatrix = camera->getViewMatrix();
    shadersMap["terrain"]->setMat4("viewMatrix", viewMatrix);
}
