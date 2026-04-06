#include <SFML/Graphics.hpp>
#include <optional>
#include <cmath> 

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Task 103 - Collision Detection");
    window.setFramerateLimit(60);

    float r1 = 40.f;
    sf::CircleShape autoCircle(r1);
    autoCircle.setFillColor(sf::Color::Red);
    autoCircle.setOrigin({r1, r1});
    autoCircle.setPosition({0.f, 300.f});

    float r2 = 40.f;
    sf::CircleShape playerCircle(r2);
    playerCircle.setFillColor(sf::Color::Blue);
    playerCircle.setOrigin({r2, r2});
    playerCircle.setPosition({400.f, 100.f}); // Center width, Y=100 (near top)

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        autoCircle.move({2.0f, 0.f});
        if (autoCircle.getPosition().x > 800 + r1) {
            autoCircle.setPosition({-r1, 300.f}); // Reset to left
        }

        float speed = 5.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    playerCircle.move({0.f, -speed});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  playerCircle.move({0.f, speed});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  playerCircle.move({-speed, 0.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) playerCircle.move({speed, 0.f});

    
        sf::Vector2f p1 = autoCircle.getPosition();
        sf::Vector2f p2 = playerCircle.getPosition();
        
        float distance = std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));

        if (distance < (r1 + r2)) {

            autoCircle.setFillColor(sf::Color::Green);
            playerCircle.setFillColor(sf::Color::Green);
        } else {
    
            autoCircle.setFillColor(sf::Color::Red);
            playerCircle.setFillColor(sf::Color::Blue);
        }

        window.clear();
        window.draw(autoCircle);
        window.draw(playerCircle);
        window.display();
    }

    return 0;
}