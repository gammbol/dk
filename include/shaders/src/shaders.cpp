//
// Created by win-114 on 25.11.2024.
//
#include <shaders.h>

Shaders::Shaders(const std::string& vss, const std::string& fss): 
  vertex(0), fragment(0), program(0) {
    std::string line;
    std::ifstream vsf(vss);
    std::ifstream fsf(fss);

    while (std::getline(vsf, line)) {
        vertexShaderSource += line;
        vertexShaderSource += "\n";
    }

    line.clear();
    vertexCode = vertexShaderSource.c_str();

    while (std::getline(fsf, line)) {
        fragmentShaderSource += line;
        fragmentShaderSource += '\n';
    }

    fragmentCode = fragmentShaderSource.c_str();


    vsf.close();
    fsf.close();
}

void Shaders::compileShaders() {
    // debug info
    int success;
    char infoLog[512];

    // compiling vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cerr << "error:shader:vertex:compilation\n" << infoLog << std::endl;
    }

    // compiling fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cerr << "error:shader:fragment:compilation\n" << infoLog << std::endl;
    }
}

void Shaders::createProgram() {
    // debug info
    int success;
    char infoLog[512];

    program = glCreateProgram();

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "error:shader:program:linking\n" << infoLog << std::endl;
    }

    // deleting the shaders
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shaders::useProgram() const {
    glUseProgram(program);
}

void Shaders::addUniform(const char *name, float a, float b, float c, float d) {
  if (program == 0) {
    std::cerr << "Program is not initialized!" << std::endl;
    return;
  }

  int vertexColorLocation = glGetUniformLocation(program, name);
  glUniform4f(vertexColorLocation, a, b, c, d);
}

Shaders::~Shaders()= default;
