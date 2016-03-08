#include "shaders/shader.hpp"
#include <cstring>
#include <fstream>


Shader::Shader(std::string const& vertexShaderFile, std::string const& fragmentShaderFile)
    : programId_(glCreateProgram())
    , vertexShaderId_(compileShader(vertexShaderFile, GL_VERTEX_SHADER))
    , fragmentShaderId_(compileShader(fragmentShaderFile, GL_FRAGMENT_SHADER))
{
    glAttachShader(programId_, vertexShaderId_  );
    glAttachShader(programId_, fragmentShaderId_);
}

Shader::~Shader() {
    stop();
    glDetachShader(programId_, vertexShaderId_);
    glDetachShader(programId_, fragmentShaderId_);
    glDeleteShader(vertexShaderId_);
    glDeleteShader(fragmentShaderId_);
    glDeleteProgram(programId_);
}

void Shader::start() const {
    glUseProgram(programId_);
}
void Shader::stop() const {
    glUseProgram(0);
}

void Shader::linkShaders() {
    bindAttributes();
    glLinkProgram(programId_);
    glValidateProgram(programId_);
    getAllUniformLocations();
}

void Shader::bindAttribute(GLuint attribute, GLchar const* variableName) {
    glBindAttribLocation(programId_, attribute, variableName);
}

GLint Shader::getUniformLocation(GLchar const* name) const {
    return glGetUniformLocation(programId_, name);
}

void Shader::loadFloat(GLint location, GLfloat value) const {
    glUniform1f(location, value);
}

void Shader::loadInteger(GLint location, GLint value) const {
    glUniform1i(location, value);
}

void Shader::loadVector2(GLint location, glm::vec2 const& value) const {
    glUniform2f(location, value.x, value.y);
}

void Shader::loadVector3(GLint location, glm::vec3 const& value) const {
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::loadMatrix(GLint location, glm::mat4 const& matrix) const {
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::readTextFromFile(std::string const& filename, char*& output){
    std::string buf = std::string("");
    std::string line;

    std::ifstream in(filename.c_str());
    while (std::getline(in, line)) {
        buf += line + "\n";
    }
    output = new char[buf.length()+1];
    strncpy(output, buf.c_str(), buf.length());
    output[buf.length()] = '\0';

    in.close();
}

void Shader::printLog(GLuint handle, std::string const& filename) {
    int infologLength = 0;
    int maxLength;

    if (glIsShader(handle)) {
        glGetShaderiv( handle, GL_INFO_LOG_LENGTH, &maxLength);
    } else {
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &maxLength);
    }

    char infoLog[maxLength];

    bool isShader;
    if (glIsShader(handle)) {
        glGetShaderInfoLog(handle, maxLength, &infologLength, infoLog);
        isShader = true;
    } else {
        glGetProgramInfoLog(handle, maxLength, &infologLength, infoLog);
        isShader = false;
    }

    if (infologLength > 0) {
        printf("[ERROR] %s Handle %d (%s): %s\n", (isShader ? "Shader" : "Program"), handle, filename.c_str(), infoLog);
    }
}

GLuint Shader::compileShader(std::string const& filename, GLenum shaderType) {
    char *shaderString;
    readTextFromFile(filename.c_str(), shaderString);

    GLuint shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, (const char**)&shaderString, NULL);

    delete [] shaderString;

    glCompileShader(shaderId);    printLog(shaderId, filename);
    return shaderId;
}
