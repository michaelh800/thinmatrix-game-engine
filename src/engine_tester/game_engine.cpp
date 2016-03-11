#include "engine_tester/game_engine.hpp"


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
        picker_.update();
        auto ray = picker_.getCurrentRay();
        // Do something with ray?
        game_.render(renderer_);
        display_.update();
    }
}
