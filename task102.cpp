#include <SFML/Graphics.hpp>
#include <optional>

int main() {
    // 1. Create the window
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Task 102 - Growing & Reset");
    
    // 2. Limit the speed so it's not too fast on your Mac
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

        // --- THE RESET LOGIC ---
        // Increase radius slowly (since we limited framerate, 1.0f is a good speed)
        radius += 1.0f; 

        // If the radius hits 300, the diameter is 600 (the full width of your window)
        if (radius >= 300.f) {
            radius = initialRadius; // Force it back to 10.f
        }

        // Update the circle with the new radius
        circle.setRadius(radius);
        
        // RE-CENTER: We must update the origin and position every time the radius changes
        circle.setOrigin({radius, radius});
        circle.setPosition({300.f, 300.f});

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}