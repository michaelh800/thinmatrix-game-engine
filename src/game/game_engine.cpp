#include "game/game_engine.hpp"
#include <iostream>


GameEngine::~GameEngine() {
    display_.close();
}

void GameEngine::run() {
    bool running = true;
    sf::Clock fpsClock;
    bool displayFps = false;

    while (running) {
        sf::Event event;
        while (display_.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed
                || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                running = false;
            } else if (event.type == sf::Event::Resized) {
                display_.resize(event.size.width, event.size.height);
                renderer_.resetProjectionMatrix();
            }
        }

        sf::Time elapsed = fpsClock.restart();
        float fps = 1000000.0f / elapsed.asMicroseconds();
        if (displayFps) std::cout << "FPS: " << fps << std::endl;

        game_.update();
        game_.render(renderer_);
        display_.update();
    }
}
