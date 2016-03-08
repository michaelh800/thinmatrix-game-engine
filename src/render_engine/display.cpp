#include "render_engine/display.hpp"


sf::Window Display::window_;

Display::Display(sf::String const& name) {
    // sf::VideoMode fullscreen = sf::VideoMode::getFullscreenModes().front();
    // window_.create(fullscreen, name, sf::Style::Fullscreen, sf::ContextSettings(32));
    window_.create(sf::VideoMode(900, 675), name, sf::Style::Default, sf::ContextSettings(32));
    window_.setVerticalSyncEnabled(true);
    window_.setPosition(sf::Vector2i(50, 25));
    window_.setMouseCursorVisible(false);
}

void Display::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void Display::update() {
    window_.display();
}

void Display::close() {
    window_.close();
}

sf::Window& Display::getWindow() {
    return window_;
}

float Display::getAspectRatio() {
    sf::Vector2u dimensions = window_.getSize();
    return (float) dimensions.x / dimensions.y;
}

sf::Vector2i Display::getMousePositionDelta() {
    sf::Vector2i center = static_cast<sf::Vector2i>(window_.getSize() / 2U);
    sf::Vector2i delta = sf::Mouse::getPosition(window_) - center;
    sf::Mouse::setPosition(center, window_);
    return delta;
}
