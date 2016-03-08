#pragma once
#include <GL/glew.h>
#include <SFML/Window.hpp>

class Display {
public:
    Display(sf::String const& name="");

    void resize(int width, int height);
    void update();
    void close();

    sf::Window& getWindow();
    static float getAspectRatio();
    static sf::Vector2i getMousePositionDelta();

private:
    static sf::Window window_;
};
