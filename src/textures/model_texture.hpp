#pragma once
#include <GL/glew.h>

class ModelTexture {
public:
    ModelTexture() = default;
    ModelTexture(GLuint textureId);

    GLuint getTextureId() const;

    GLfloat getShineDamper() const;
    void setShineDamper(GLfloat shineDamper);

    GLfloat getReflectivity() const;
    void setReflectivity(GLfloat reflectivity);

    GLboolean hasTransparency() const;
    void setTransparency(GLboolean hasTransparency);

    GLboolean usesFakeLighting() const;
    void setFakeLighting(GLboolean usesFakeLighting);

    int getNumberOfRows() const;
    void setNumberOfRows(int numberOfRows);

private:
    GLuint textureId_;
    GLfloat shineDamper_;
    GLfloat reflectivity_;
    GLboolean hasTransparency_;
    GLboolean usesFakeLighting_;
    int numberOfRows_;
};
