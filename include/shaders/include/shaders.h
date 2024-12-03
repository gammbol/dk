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
    int isRunning() const;
    void addUniform(const char *name, float a, float b, float c, float d);
    void setInt(const char *name, int a);
    void setFloat(const char *name, float a);
    void setDouble(const char *name, double a);
    void setUInt(const char *name, unsigned int a);
    void setBool(const char *name, bool a);
    void setVec2(const char *name, int a, int b);
    void setVec3(const char *name, int a, int b, int c);
    void setVec4(const char *name, int a, int b, int c, int d);
    void setVec3f(const char *name, float a, float b, float c);
    ~Shaders();
};

#endif //SHADERS_H
