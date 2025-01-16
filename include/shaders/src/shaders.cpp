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

int Shaders::isRunning() const {
  if (!program) {
    std::cerr << "Program is not running!" << std::endl;
    return 0;
  }
  return 1;
}

unsigned int Shaders::getUniLoc(const char *name) const {
  if (!isRunning()) return 0;

  return glGetUniformLocation(program, name);
}

void Shaders::addUniform(const char *name, float a, float b, float c, float d) {
  if (!isRunning()) return;

  int nameLocation = glGetUniformLocation(program, name);
  glUniform4f(nameLocation, a, b, c, d);
}

void Shaders::setInt(const char *name, int a) {
  if (!isRunning()) return;

  int nameLocation = glGetUniformLocation(program, name);
  glUniform1i(nameLocation, a);
}

void Shaders::setFloat(const char *name, float a) {
  if (!isRunning()) return;

  int nameLocation = glGetUniformLocation(program, name);
  glUniform1f(nameLocation, a);
}

void Shaders::setDouble(const char *name, double a) {
  if (!isRunning()) return;

  int nameLocation = glGetUniformLocation(program, name);
  glUniform1d(nameLocation, a);
}

void Shaders::setUInt(const char *name, unsigned int a) {
  if (!isRunning()) return;

  int nameLocation = glGetUniformLocation(program, name);
  glUniform1ui(nameLocation, a);
}

void Shaders::setBool(const char *name, bool a) {
  if (!isRunning()) return;

  int nameLocation = glGetUniformLocation(program, name);
  glUniform1i(nameLocation, a);
}

void Shaders::setVec2(const char *name, int a, int b) {
  if (!isRunning()) return;

  int nameLocation = glGetUniformLocation(program, name);
  glUniform2i(nameLocation, a, b);
}

void Shaders::setVec3(const char *name, int a, int b, int c) {
  if (!isRunning()) return;

  int nameLocation = glGetUniformLocation(program, name);
  glUniform3i(nameLocation, a, b, c);
}

void Shaders::setVec4(const char *name, int a, int b, int c, int d) {
  if (!isRunning()) return;

  int nameLocation = glGetUniformLocation(program, name);
  glUniform4i(nameLocation, a, b, c, d);
}

void Shaders::setVec3f(const char *name, glm::vec3 vec) {
  if (!isRunning()) return;

  int nameLocation = glGetUniformLocation(program, name);
  glUniform3f(nameLocation, vec.x, vec.y, vec.z);
}

void Shaders::setMat4(const char *name, glm::mat4 mat) {
  if (!isRunning()) return;

  int matLoc = glGetUniformLocation(program, name);
  glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(mat));
}

Shaders::~Shaders()= default;
