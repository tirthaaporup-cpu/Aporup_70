#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// --- GLOBAL CONFIGURATION ---
const int GRID_SIZE = 20;       // Size of each grid square (20x20 pixels)
const int WINDOW_WIDTH = 800;   // Width of the screen
const int WINDOW_HEIGHT = 600;  // Height of the screen

enum class Direction { Up, Down, Left, Right };

// --- 1. THE SNAKE CLASS ---
class Snake {
public:
    std::vector<sf::Vector2f> body; // Holds positions of all snake segments
    Direction dir;
    bool mustGrow;

    // Constructor: Initializes the snake setup
    Snake() {
        reset();
    }

    // Resets snake to default state at center screen
    void reset() {
        body.clear();
        // Start with 3 segments in the center area
        body.push_back(sf::Vector2f(400.0f, 300.0f)); // Head
        body.push_back(sf::Vector2f(380.0f, 300.0f)); // Body segment 1
        body.push_back(sf::Vector2f(360.0f, 300.0f)); // Body segment 2
        
        dir = Direction::Right; // Start moving right
        mustGrow = false;
    }

    // Handles movement logic
    void move() {
        // Calculate where the new head position should be
        sf::Vector2f oldHead = body.front();
        sf::Vector2f newHead = oldHead;

        if (dir == Direction::Up)    newHead.y -= GRID_SIZE;
        if (dir == Direction::Down)  newHead.y += GRID_SIZE;
        if (dir == Direction::Left)  newHead.x -= GRID_SIZE;
        if (dir == Direction::Right) newHead.x += GRID_SIZE;

        // Insert new head at the front
        body.insert(body.begin(), newHead);

        // Growth logic
        if (mustGrow) {
            mustGrow = false; // We grew! Reset flag, don't delete tail segment
        } else {
            body.pop_back();  // Didn't eat food? Remove the tail segment to keep size constant
        }
    }

    // Request growth on next update cycle
    void grow() {
        mustGrow = true;
    }
};

// --- GLOBAL VARIABLES ---
Snake playerSnake;
sf::Vector2f foodPos;
int playerScore = 0;
bool isGameOver = false;

// --- FUNCTION DECLARATIONS ---
void generateFood();
void checkCollisions();
void handleInput();
void updateGame();
void renderGame(sf::RenderWindow& window, sf::Font& font);

// --- MAIN FUNCTION ---
int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Snake Assignment Game");
    window.setFramerateLimit(10); // Lower speed to make it playable

    // Load default system font for Score/Game Over display
    sf::Font font;
    if (!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        // Fallback font load attempt if first path fails on older macOS versions
        font.openFromFile("/System/Library/Fonts/Courier.dfont");
    }

    generateFood(); // Spawn first food piece

    // --- MAIN GAME LOOP ---
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Only update logic if game is actively running
        if (!isGameOver) {
            handleInput();
            updateGame();
        } else {
            // Press Enter to restart when game is over
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                playerSnake.reset();
                playerScore = 0;
                isGameOver = false;
                generateFood();
            }
        }

        renderGame(window, font);
    }

    return 0;
}

// --- FUNCTION DEFINITIONS ---

// Randomly positions food snapped to our layout grid
void generateFood() {
    int columns = WINDOW_WIDTH / GRID_SIZE;  // 40 columns
    int rows = WINDOW_HEIGHT / GRID_SIZE;    // 30 rows

    foodPos.x = static_cast<float>((std::rand() % columns) * GRID_SIZE);
    foodPos.y = static_cast<float>((std::rand() % rows) * GRID_SIZE);
}

void handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && playerSnake.dir != Direction::Down)
        playerSnake.dir = Direction::Up;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && playerSnake.dir != Direction::Up)
        playerSnake.dir = Direction::Down;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && playerSnake.dir != Direction::Right)
        playerSnake.dir = Direction::Left;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && playerSnake.dir != Direction::Left)
        playerSnake.dir = Direction::Right;
}

void updateGame() {
    playerSnake.move();
    checkCollisions();
}

void checkCollisions() {
    sf::Vector2f head = playerSnake.body.front();

    // 1. Game Boundary Collisions
    if (head.x < 0 || head.x >= WINDOW_WIDTH || head.y < 0 || head.y >= WINDOW_HEIGHT) {
        isGameOver = true;
    }

    // 2. Self Collision Detection
    for (size_t i = 1; i < playerSnake.body.size(); ++i) {
        if (head == playerSnake.body[i]) {
            isGameOver = true;
        }
    }

    // 3. Food Consumption Collision
    if (head == foodPos) {
        playerSnake.grow();   // Increase Snake Size
        playerScore += 10;    // Increase Score tracking metric
        generateFood();       // Respawn target item
    }
}

void renderGame(sf::RenderWindow& window, sf::Font& font) {
    window.clear(sf::Color(20, 20, 20)); // Soft dark gray background

    sf::RectangleShape drawBlock(sf::Vector2f(GRID_SIZE - 2.0f, GRID_SIZE - 2.0f));

    // Draw Food (Red)
    drawBlock.setFillColor(sf::Color::Red);
    drawBlock.setPosition(foodPos);
    window.draw(drawBlock);

    // Draw Snake (Cyan Head, Green Body)
    for (size_t i = 0; i < playerSnake.body.size(); ++i) {
        if (i == 0) {
            drawBlock.setFillColor(sf::Color::Cyan);
        } else {
            drawBlock.setFillColor(sf::Color::Green);
        }
        drawBlock.setPosition(playerSnake.body[i]);
        window.draw(drawBlock);
    }

    // Draw Live Score Display UI
    sf::Text scoreText(font, "Score: " + std::to_string(playerScore), 24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({20.0f, 15.0f});
    window.draw(scoreText);

    // --- GAME OVER OVERLAY SCREEN ---
    if (isGameOver) {
        // Draw matching overlay background shield mask
        sf::RectangleShape dimMask(sf::Vector2f(static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT)));
        dimMask.setFillColor(sf::Color(0, 0, 0, 200)); // semi-transparent black overlay
        window.draw(dimMask);

        sf::Text lostText(font, "GAME OVER", 50);
        lostText.setFillColor(sf::Color::Red);
        lostText.setPosition({260.0f, 200.0f});
        window.draw(lostText);

        sf::Text finalScoreText(font, "Final Score: " + std::to_string(playerScore), 30);
        finalScoreText.setFillColor(sf::Color::White);
        finalScoreText.setPosition({300.0f, 280.0f});
        window.draw(finalScoreText);

        sf::Text restartText(font, "Press Enter to Restart Game", 20);
        restartText.setFillColor(sf::Color::Yellow);
        restartText.setPosition({265.0f, 360.0f});
        window.draw(restartText);
    }

    window.display();
}