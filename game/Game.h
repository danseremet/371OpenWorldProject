//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_GAME_H
#define OPENWORLD_GAME_H

#define GLEW_STATIC 1 // necessary for glew
#include <iostream>
#include <list>

#include <irrKlang.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include "../shader/Shader.h"
#include "../window/WindowManager.h"
#include "../player/Player.h"
#include "../camera/Camera.h"
#include "../model/Model.h"
#include "../model/TerrainModel.h"
#include "../model/CubeModel.h"
#include "../model/TreeModel.h"
#include "../model/RockModel.h"
#include "../texture/Texture.h"
#include "../terrain_generator/TerrainGenerator.h"
#include "../generators/PerlinNoiseGenerator.h"
#include "../generators/ColorGenerator.h"


class Game {
public:
    Game();

    ~Game();

    Player* getPlayer() const;
    Camera* getCamera() const;
    Shader* getShader() const;
    GLFWwindow* getWindow() const;

    double lastMousePosX;
    double lastMousePosY;

    GLfloat dt;

    GLint vbo;


    GLint polygonMode;

    void launch();

    GLfloat getFovy() const;

    void setFovy(GLfloat fovy);

    GLuint getScrWidth() const;

    GLuint getScrHeight() const;

    void setScrWidth(GLuint scrWidth);

    void setScrHeight(GLuint scrHeight);

    void updateAspectRatio();

    void updateProjectionMatrix();

    const std::map<int, std::map<int, Model *>> &getRocks() const;

    bool  cameraFirstPerson;

    GLfloat findTerrainYat(float z, float x);
    bool playerOnGround();

    GLfloat gravity;

private:

    void gameLoop();

    void frameSetup();

    void frameEnd();

    Player* player;
    Camera *camera;
    GLFWwindow *window;
    Shader *shader;

    std::map<int, std::map<int, Model*>> terrain;
    std::map<int, std::map<int, Model*>> rocks;
    std::map<int, std::map<int, Model*>> trees;

    TerrainGenerator *terrainGenerator;

    GLfloat lastFrameTime;

    void drawModels();

    void chunkLoading();

    void chunkUnloading();

    void playerPhysics();

    glm::mat4 createProjectionMatrix();

    GLfloat computeAspectRatio();

    glm::mat4 projectionMatrix;

    glm::mat4 viewMatrix;

    GLfloat fovy;

    GLuint scrWidth;
    GLuint scrHeight;

    GLfloat aspect;

    GLfloat zNear;
    GLfloat zFar;

    const GLuint SHADOW_WIDTH = 1024;
    const GLuint SHADOW_HEIGHT = 1024;

    int chunkSize;

    int numberOfChunks;

    int startChunk;

    int numberOfRocks;
    int numberOfTrees;

    std::map<std::string, Shader*> shadersMap;

    std::map<std::string, Texture*> texturesMap;

    void setupBasicShader();

    int chunkLoadingCounter;
    int chunkUnloadingCounter;
    int chunkLoadingDuration;
    int chunkUnloadingDuration;
};

#endif //OPENWORLD_GAME_H
