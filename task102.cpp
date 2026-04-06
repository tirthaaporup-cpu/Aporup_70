#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Task 102 - Growing & Reset");
    
    
    window.setFramerateLimit(60); 

    float initialRadius = 10.f;
    float radius = initialRadius;
    
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

    
        radius += 1.0f; 

        
        if (radius >= 300.f) {
            radius = initialRadius; 
        }

        
        circle.setRadius(radius);
        
        
        circle.setOrigin({radius, radius});
        circle.setPosition({300.f, 300.f});

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}