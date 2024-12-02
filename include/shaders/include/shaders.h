//
// Created by win-114 on 25.11.2024.
//

#ifndef SHADERS_H
#define SHADERS_H

#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>

class Shaders {
    unsigned int vertex, fragment;
    unsigned int program;
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    const char* vertexCode;
    const char* fragmentCode;

public:
    Shaders(const std::string& vss, const std::string& fss);
    void compileShaders();
    void createProgram();
    void useProgram() const;
    void addUniform(const char *name, float a, float b, float c, float d);
    ~Shaders();
};

#endif //SHADERS_H
