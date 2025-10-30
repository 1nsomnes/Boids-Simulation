#include "Manager/SimulationManager.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Window/ContextSettings.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/WindowEnums.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

using namespace sf;

const int width = 800u;
const int height = 600u;

const float speed = 15.0f;

int main() {
    ContextSettings settings;
    settings.antiAliasingLevel = 8;
    RenderWindow window(VideoMode({width, height}), "Boids", Style::Default, State::Windowed, settings);


    Clock deltaClock;
    SimulationManager manager(10, width, height);

    while (window.isOpen()) {
        // pollEvent returns std::optional<Event>
        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }

        float deltaTime = deltaClock.restart().asSeconds();
        float distance = deltaTime * speed;

        manager.move_boids(distance);
        manager.apply_boid_behavior(deltaTime);
        manager.reset_edge();

        window.clear();
        for(const auto* shape: manager.get_shapes()) {
          window.draw(*shape);
        }
        manager.draw_direction_lines(window);
        window.display();
    }
    return 0;
}
