#include "game/game_engine.hpp"


GameEngine::~GameEngine() {
    display_.close();
}

void GameEngine::run() {
    bool running = true;

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

        game_.update();
        game_.render(renderer_);
        display_.update();
    }
}
