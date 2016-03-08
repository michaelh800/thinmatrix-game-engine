#include "guis/gui_renderer.hpp"
#include "toolbox/math.hpp"


GuiRenderer::GuiRenderer(Loader &loader) {
    std::vector<GLfloat> positions = { -1, 1, -1, -1, 1, 1, 1, -1 };
    quad_ = loader.loadToVao(positions, 2);
}

void GuiRenderer::render(std::vector<GuiTexture> const& guis) {
    shader_.start();
    glBindVertexArray(quad_.getVaoId());
    glEnableVertexAttribArray(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    for (GuiTexture const& gui : guis) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gui.getTextureId());
        glm::mat4 transformationMatrix =
            Math::createTransformationMatrix(gui.getPosition(), gui.getScale());
        shader_.loadTransformationMatrix(transformationMatrix);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, quad_.getVertexCount());
    }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    shader_.stop();
}
