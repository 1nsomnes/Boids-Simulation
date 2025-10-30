#include "SFML/System/Clock.hpp"
#include "SFML/Window/ContextSettings.hpp"
#include "SFML/Window/WindowEnums.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

using namespace sf;

int main() {
    ContextSettings settings;
    settings.antiAliasingLevel = 8;

    RenderWindow window(VideoMode({800u, 600u}), "Boids", Style::Default, State::Windowed, settings);

    CircleShape shape(100.f,3);
    shape.setFillColor(Color::White);
    shape.setPosition({200.f, 150.f});

    float speed = 2.0f;

    Clock deltaClock;

    while (window.isOpen()) {
        // pollEvent returns std::optional<Event>
        while (auto event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
            if (event->is<Event::KeyPressed>()) {
               
              shape.move({10.0f, 0.0f});
            }
        }

        Time deltaTime = deltaClock.restart();   
        shape.move({deltaTime.asSeconds() * speed, 0.0f});
        Vector2f test = shape.getPosition();

        window.clear();
        window.draw(shape);
        window.display();
    }
    return 0;
}
