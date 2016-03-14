#include "shaders/shader.hpp"
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <cstring>
#include <fstream>


Shader::Shader(std::string const& vertexShaderFile, std::string const& fragmentShaderFile)
    : program_(glCreateProgram())
    , vertexShaderFile_(vertexShaderFile)
    , fragmentShaderFile_(fragmentShaderFile)
{ }

Shader::~Shader() {
    if (program_.get()) {
        stop();
    }
}

void Shader::start() const {
    glUseProgram(program_.get());
}
void Shader::stop() const {
    glUseProgram(0);
}

void Shader::initialize() {
    gl::ShaderHandle vertexShader(compileShader(vertexShaderFile_, GL_VERTEX_SHADER));
    gl::ShaderHandle fragmentShader(compileShader(fragmentShaderFile_, GL_FRAGMENT_SHADER));

    glAttachShader(program_.get(), vertexShader.get());
    glAttachShader(program_.get(), fragmentShader.get());

    bindAttributes();
    glLinkProgram(program_.get());
    glValidateProgram(program_.get());
    getAllUniformLocations();

    glDetachShader(program_.get(), vertexShader.get());
    glDetachShader(program_.get(), fragmentShader.get());
}

void Shader::bindAttribute(GLuint attribute, GLchar const* variableName) {
    glBindAttribLocation(program_.get(), attribute, variableName);
}

GLint Shader::getUniformLocation(GLchar const* name) const {
    return glGetUniformLocation(program_.get(), name);
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

void Shader::loadVector4(GLint location, glm::vec4 const& value) const {
    glUniform4f(location, value.x, value.y, value.z, value.w);
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
