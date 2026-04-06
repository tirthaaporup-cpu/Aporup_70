#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Task 101 - Centered Circle");
    
    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Green);
    circle.setOrigin({50.f, 50.f});
    circle.setPosition({300.f, 300.f});

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}




