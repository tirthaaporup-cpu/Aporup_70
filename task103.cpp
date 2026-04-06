#include <SFML/Graphics.hpp>
#include <optional>
#include <cmath> // For sqrt

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Task 103 - Collision Detection");
    window.setFramerateLimit(60);

    // 1. Auto Moving Circle (Red)
    float r1 = 40.f;
    sf::CircleShape autoCircle(r1);
    autoCircle.setFillColor(sf::Color::Red);
    autoCircle.setOrigin({r1, r1});
    autoCircle.setPosition({0.f, 300.f});

    // 2. Player Controlled Circle (Blue)
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

        // --- 1. AUTO MOVEMENT ---
        autoCircle.move({2.0f, 0.f});
        if (autoCircle.getPosition().x > 800 + r1) {
            autoCircle.setPosition({-r1, 300.f}); // Reset to left
        }

        // --- 2. PLAYER MOVEMENT ---
        float speed = 5.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    playerCircle.move({0.f, -speed});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  playerCircle.move({0.f, speed});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  playerCircle.move({-speed, 0.f});
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) playerCircle.move({speed, 0.f});

        // --- 3. COLLISION DETECTION ---
        sf::Vector2f p1 = autoCircle.getPosition();
        sf::Vector2f p2 = playerCircle.getPosition();
        
        // Distance formula: sqrt(dx^2 + dy^2)
        float distance = std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));

        if (distance < (r1 + r2)) {
            // Visual Effect: Turn both Yellow on collision
            autoCircle.setFillColor(sf::Color::Yellow);
            playerCircle.setFillColor(sf::Color::Yellow);
        } else {
            // Back to original colors
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