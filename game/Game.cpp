//
// Created by danseremet on 2020-04-04.
//

#include "Game.h"
#include "../keyboard/Keyboard.h"

using namespace glm;
using namespace std;
using namespace irrklang;


Game::Game() {

    // Window setup
    window = WindowManager::getWindow();

  

    // Shader loading
    shadersMap = std::map<std::string, Shader *>{};
    shadersMap["basic"] = new Shader{"basic"};

    // Setup P & V matrix properties
    fovy = 70.0f;
    scrWidth = WindowManager::getDefaultScreenWidth();
    scrHeight = WindowManager::getDefaultScreenHeight();
    aspect = computeAspectRatio();
    zNear = 0.01f;
    zFar = 3000.0f;     // careful
    projectionMatrix = createProjectionMatrix();

    // Generate Terrain
    auto *perlinNoiseGenerator = new PerlinNoiseGenerator(0.35f, 3, 100.0f);
    auto *colorGenerator = new ColorGenerator(0.55f);
    terrainGenerator = new TerrainGenerator(perlinNoiseGenerator, colorGenerator, shadersMap, texturesMap);

    // Model creation
    startChunk = 20;

    this->chunkLoadingCounter = 0;
    this->chunkUnloadingCounter = 0;
    chunkUnloadingDuration = 1;
    chunkLoadingDuration = 1;
    chunkSize = 50;
    numberOfChunks = 4; // careful N*2 memory

    int initialPos{startChunk * chunkSize};
    int chunkX_neg{startChunk - numberOfChunks};
    int chunkX_pos{startChunk + numberOfChunks};
    int chunkZ_neg{startChunk - numberOfChunks};
    int chunkZ_pos{startChunk + numberOfChunks};


    numberOfRocks = 0.15 * chunkSize;
    numberOfTrees = 0.90 * chunkSize;

    float playerY{0.0f};

    for (int z{chunkZ_neg}; z <= chunkZ_pos; z++) {
        terrain.insert(make_pair(z, map<int, Model *>()));
        rocks.insert(make_pair(z, map<int, Model *>()));
        trees.insert(make_pair(z, map<int, Model *>()));

        for (int x{chunkX_neg}; x <= chunkX_pos; x++) {

            Model *terrainModel = terrainGenerator->generateTerrain(chunkSize, x, z);
            terrainModel->loadModel();
            terrain[z].insert(make_pair(x, terrainModel));

            auto heights = ((TerrainModel *) terrainModel)->getHeights();
            if (z == startChunk && x == startChunk) {
                playerY = heights[0][0];
            }

            Model *rockModel = new RockModel{shadersMap, texturesMap, x, z, chunkSize, heights, numberOfRocks};
            rockModel->loadModel();
            rocks[z].insert(make_pair(x, rockModel));

            Model* treeModel = new TreeModel{ shadersMap, texturesMap, x, z, chunkSize, heights, numberOfTrees, perlinNoiseGenerator }; // Call the treeModel
            treeModel->loadModel();
            trees[z].insert(make_pair(x, treeModel));
        }
    }

    // Player setup
    glm::vec3 player_pos{ initialPos, playerY, initialPos };
    player = new Player{ player_pos };
    gravity = 3.5f;

    // Camera setup
    glm::vec3 camera_pos{ player->x, player->y + player->height, player->z};
    camera = new Camera{ camera_pos };
    cameraFirstPerson = true;

    viewMatrix = camera->getViewMatrix();

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

    ISoundEngine* SoundEngine = createIrrKlangDevice();
    if (SoundEngine) {
        SoundEngine->play2D("../audio/Ground Waves.wav", GL_TRUE);
    }
   
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
    chunkLoading();
    chunkUnloading();
    playerPhysics();
    collisionDetection();
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
    map<int, map<int, Model *>>::iterator itr;
    map<int, Model *>::iterator ptr;
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

void Game::chunkLoading() {

    // Run chunk loading every 100 frames
    this->chunkLoadingCounter++;
    if (chunkLoadingCounter != chunkLoadingDuration) {
        return;
    }
    // reset chunk loading counter
    this->chunkLoadingCounter = 0;

    // center of chunk loading
    int chunkCenterX = static_cast<int>(camera->cameraPosition.x / chunkSize);
    int chunkCenterZ = static_cast<int>(camera->cameraPosition.z / chunkSize);

    // boundaries of chunk loading
    int chunkXHigh = chunkCenterX + numberOfChunks;
    int chunkXLow = chunkCenterX - numberOfChunks;
    int chunkZHigh = chunkCenterZ + numberOfChunks;
    int chunkZLow = chunkCenterZ - numberOfChunks;

    // load one chunk
    bool oneChunkLoaded = false;

    // loop over z chunks
    for (int z{chunkZLow}; z <= chunkZHigh; z++) {

        // add a row if z key doesn't exist
        if (terrain.find(z) == terrain.end()) {
            terrain.insert(make_pair(z, map<int, Model *>()));
            rocks.insert(make_pair(z, map<int, Model *>()));
            trees.insert(make_pair(z, map<int, Model *>()));
        }

        // loop over x chunks
        for (int x{chunkXLow}; x <= chunkXHigh; x++) {

            // add a column of models if x key doesn't exit
            if (terrain[z].find(x) == terrain[z].end()) {

                // Add terrain
                Model *terrainModel = terrainGenerator->generateTerrain(chunkSize, x, z);
                terrainModel->loadModel();
                terrain[z].insert(make_pair(x, terrainModel));

                auto heights = ((TerrainModel *) terrainModel)->getHeights();

                // Add rocks
                Model *rockModel = new RockModel{shadersMap, texturesMap, x, z, chunkSize, heights, numberOfRocks};
                rockModel->loadModel();
                rocks[z].insert(make_pair(x, rockModel));

                // Add trees
                auto *perlinNoiseGenerator = new PerlinNoiseGenerator(0.35f, 3, 100.0f);
                Model *treeModel = new TreeModel{shadersMap, texturesMap, x, z, chunkSize, heights, numberOfTrees, perlinNoiseGenerator};
                treeModel->loadModel();
                trees[z].insert(make_pair(x, treeModel));

                oneChunkLoaded = true;
                break;
            }

        }

        // stop loading more chunks after one chunk is loaded for these 100 frames
        if (oneChunkLoaded) {
            break;
        }

    }
}

void Game::chunkUnloading() {

    // Run chunk unloading every 100 frames
    this->chunkUnloadingCounter++;
    if (chunkUnloadingCounter != chunkUnloadingDuration) {
        return;
    }
    // reset chunk unloading counter
    this->chunkUnloadingCounter = 0;

    // center of chunk unloading
    int chunkCenterX = static_cast<int>(camera->cameraPosition.x / chunkSize);
    int chunkCenterZ = static_cast<int>(camera->cameraPosition.z / chunkSize);

    // boundaries of chunk unloading
    int chunkXHigh = chunkCenterX + numberOfChunks;
    int chunkXLow = chunkCenterX - numberOfChunks;
    int chunkZHigh = chunkCenterZ + numberOfChunks;
    int chunkZLow = chunkCenterZ - numberOfChunks;

    // unload one chunk
    bool oneChunkUnloaded = false;

    // loop over every z key
    for (auto it = terrain.cbegin(); it != terrain.cend() ; it++) {

        int z = it->first;

        // loop over every x col key in a loaded z row
        for (auto it_inner = terrain[z].cbegin(); it_inner != terrain[z].cend(); it_inner++) {

            int x = it_inner->first;

            // unload a chunk if outside X bounds
            if (x < chunkXLow || x > chunkXHigh || z < chunkZLow || z > chunkZHigh) {
                terrain[z].erase(x);
                rocks[z].erase(x);
                trees[z].erase(x);

                oneChunkUnloaded = true;
                break;
            }
        }

        // when the row is empty remove it
        if (terrain[z].empty()) {
            terrain.erase(z);
        }

        // stop unloading more chunks after one chunk is unloaded for these 100 frames
        if (oneChunkUnloaded) {
            break;
        }
    }
}

void Game::playerPhysics() {
    if (playerOnGround())
    {
        float terrainY = findTerrainYat(player->z, player->x);
        player->y = terrainY;
        if (player->verticalVelocity < -gravity)
        {
            player->verticalVelocity = -gravity;
        }
    } else
    {
        player->verticalVelocity -= gravity;
        if (player->verticalVelocity < -20)
        {
            player->verticalVelocity = -20;
        }
    }
    player->y += player->verticalVelocity * dt;


}

void Game::collisionDetection() {
    int positionChunkZ = floor(player->z / chunkSize);
    int positionChunkX = floor(player->x / chunkSize);
    for (BoxCollider* collider : rocks[positionChunkZ][positionChunkX]->colliders) {
        if (player->x <= collider->xMax && player->x >= collider->xMin && player->z <= collider->zMax && player->z >= collider->zMin)
        {
            cout << "collision detected" << endl;
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

Player* Game::getPlayer() const {
    return player;
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


GLfloat Game::findTerrainYat(float z, float x) {
    int positionChunkZ = floor(z / chunkSize);
    int positionChunkX = floor(x / chunkSize);

    auto heights = ((TerrainModel*)terrain[positionChunkZ][positionChunkX])->getHeights();

    float relativePosZ = z - positionChunkZ * chunkSize;
    float relativePosX = x - positionChunkX * chunkSize;

    int relativePosZ0 = floor(relativePosZ);
    int relativePosX0 = floor(relativePosX);
    int relativePosZ1 = floor(relativePosZ + 1);
    int relativePosX1 = floor(relativePosX + 1);

    float terrainY00 = heights[relativePosZ0][relativePosX0];
    float terrainY01 = heights[relativePosZ0][relativePosX1];
    float terrainY10 = heights[relativePosZ1][relativePosX0];
    float terrainY11 = heights[relativePosZ1][relativePosX1];

    float terrainY = bilerp(terrainY00, terrainY10, terrainY01, terrainY11,
        (relativePosZ - relativePosZ0) / (relativePosZ1 - relativePosZ0),
        (relativePosX - relativePosX0) / (relativePosX1 - relativePosX0));
    return terrainY;
}

bool Game::playerOnGround() {
    float terrainY = findTerrainYat(player->z, player->x);
    return player->y <= terrainY;
}


const GLfloat Game::bilerp(GLfloat P00, GLfloat P10, GLfloat P01, GLfloat P11, GLfloat FracZ, GLfloat FracX) const {
    GLfloat value = P00 * (1 - FracZ) * (1 - FracX)
                  + P10 * FracZ * (1 - FracX)
                  + P01 * (1 - FracZ) * FracX
                  + P11 * FracZ * FracX;
    return value;
}