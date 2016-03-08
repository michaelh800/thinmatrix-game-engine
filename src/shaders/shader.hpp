#pragma once
#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader {
public:
    Shader(std::string const& vertexShaderFile, std::string const& fragmentShaderFile);
    ~Shader();

    void start() const;
    void stop() const;

protected:
    GLuint programId_;
    GLuint vertexShaderId_, fragmentShaderId_;

    void linkShaders();
    virtual void bindAttributes() = 0;
    void bindAttribute(GLuint attribute, GLchar const* variableName);

    virtual void getAllUniformLocations() = 0;
    GLint getUniformLocation(GLchar const* name) const;
    void loadFloat  (GLint location, GLfloat value) const;
    void loadInteger(GLint location, GLint value) const;
    void loadVector2(GLint location, glm::vec2 const& value) const;
    void loadVector3(GLint location, glm::vec3 const& value) const;
    void loadMatrix (GLint location, glm::mat4 const& matrix) const;

    void printLog(GLuint handle, std::string const& filename="");

private:
    void readTextFromFile(std::string const& filename, char*& output);
    GLuint compileShader(std::string const& filename, GLenum shaderType);
};
