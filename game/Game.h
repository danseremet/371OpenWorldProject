//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_GAME_H
#define OPENWORLD_GAME_H

#define GLEW_STATIC 1 // necessary for glew
#include <iostream>
#include <list>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include "../shader/Shader.h"
#include "../window/WindowManager.h"
#include "../camera/Camera.h"
#include "../model/Model.h"
#include "../model/TerrainModel.h"
#include "../model/CubeModel.h"
#include "../model/RockModel.h"
#include "../texture/Texture.h"
#include "../terrain_generator/TerrainGenerator.h"
#include "../generators/PerlinNoiseGenerator.h"
#include "../generators/ColorGenerator.h"


class Game {
public:
    Game();

    ~Game();

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

    Model* getRockModel() const;

private:

    void gameLoop();

    void frameSetup();

    void frameEnd();

    Camera *camera;
    GLFWwindow *window;
    Shader *shader;

    Model *terrainModel;
    Model *cubeModel;
    Model *rockModel;

    TerrainGenerator *terrainGenerator;

    GLfloat lastFrameTime;

    void drawModels();
    void drawRock();

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

    std::map<std::string, Shader*> shadersMap;

    std::map<std::string, Texture*> texturesMap;

    void setupBasicShader();
    void setupTerrainShader();
};

#endif //OPENWORLD_GAME_H
