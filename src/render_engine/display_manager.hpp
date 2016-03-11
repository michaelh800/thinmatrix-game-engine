#pragma once
#include <GL/glew.h>
#include <SFML/Window.hpp>

class DisplayManager {
public:
    DisplayManager(sf::String const& name="");

    void resize(int width, int height);
    void update();
    void close();

    static sf::Window& getWindow();
    static float getAspectRatio();
    static sf::Time const& getFrameTime();
    static sf::Vector2i getMousePositionDelta();

private:
    static sf::Window window_;
    static sf::Clock clock_;
    static sf::Time frameTime_;
};
