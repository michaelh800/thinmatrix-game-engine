#include "render_engine/display_manager.hpp"


sf::Window DisplayManager::window_;
sf::Clock  DisplayManager::clock_;
sf::Time   DisplayManager::frameTime_;

DisplayManager::DisplayManager(sf::String const& name) {
    window_.create(sf::VideoMode(900, 675), name, sf::Style::Default, sf::ContextSettings(32));
    window_.setVerticalSyncEnabled(true);
    window_.setPosition(sf::Vector2i(50, 25));
    window_.setMouseCursorVisible(false);
}

void DisplayManager::resize(int width, int height) {
    glViewport(0, 0, width, height);
}

void DisplayManager::update() {
    frameTime_ = clock_.restart();
    window_.display();
}

void DisplayManager::close() {
    window_.close();
}

sf::Window& DisplayManager::getWindow() {
    return window_;
}

float DisplayManager::getAspectRatio() {
    sf::Vector2u dimensions = window_.getSize();
    return (float) dimensions.x / dimensions.y;
}

sf::Time const& DisplayManager::getFrameTime() {
    return frameTime_;
}

sf::Vector2i DisplayManager::getMousePositionDelta() {
    sf::Vector2i center = static_cast<sf::Vector2i>(window_.getSize() / 2U);
    sf::Vector2i delta = sf::Mouse::getPosition(window_) - center;
    sf::Mouse::setPosition(center, window_);
    return delta;
}
