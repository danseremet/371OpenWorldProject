//
// Created by danseremet on 2020-04-04.
//

#ifndef OPENWORLD_TEXTURE_H
#define OPENWORLD_TEXTURE_H

#define GLEW_STATIC 1 // necessary for glew

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Texture {

public:
    explicit Texture(const char* textureName);

    GLuint getId() const;

    void use() const;
private:
    GLuint ID;

    unsigned int loadTexture(char const * path);
};


#endif //OPENWORLD_TEXTURE_H
