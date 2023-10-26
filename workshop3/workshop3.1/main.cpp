// cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -S ./workshop1.1/ -B ./workshop1.1/
#include <SFML/Graphics.hpp>
#include <iostream>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int RADIUS = 50;
constexpr int CH_SIZE = 20;
constexpr float SPEED_Y = 200.f;
constexpr float G = 98.f;

struct circleName
{
    sf::CircleShape circle;
    sf::Text name;
    sf::Font font;
    sf::Vector2f pos;
    sf::Vector2f v;
    sf::Clock clock;
    float preTime;
};

void updatePosBall(circleName& ball)
{
    ball.circle.setPosition(ball.pos);
    ball.name.setPosition(ball.pos);
}

void init(circleName& ball)
{
    ball.pos = { WINDOW_WIDTH / 2, WINDOW_HEIGHT - RADIUS };
    ball.v = { 0, 0 };
    ball.circle.setRadius(RADIUS);
    ball.circle.setOrigin({ RADIUS, RADIUS });
    ball.circle.setPosition(ball.pos);
    ball.circle.setFillColor(sf::Color(255, 150, 0));
    ball.circle.setOutlineColor(sf::Color(0, 100, 255));
    ball.circle.setOutlineThickness(5.f);

    const char nameStr[] = "MDM";
    ball.font.loadFromFile("arial.ttf");
    ball.name.setFont(ball.font);
    ball.name.setString(nameStr);
    ball.name.setCharacterSize(CH_SIZE);
    ball.name.setFillColor(sf::Color(0, 0, 0));
    sf::Vector2f sizeName = ball.name.getLocalBounds().getSize();
    ball.name.setOrigin({ sizeName.x / 2, (float)(sizeName.y / 1.2) });
    ball.name.setPosition(ball.pos);

    ball.preTime = ball.clock.getElapsedTime().asSeconds();
}

void pollEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void update(circleName& ball)
{
    if (ball.pos.y + RADIUS >= WINDOW_HEIGHT)
        ball.v.y = -SPEED_Y;
    float time = ball.clock.getElapsedTime().asSeconds();
    float dt = time - ball.preTime;
    float offsetV = dt * G;
    ball.v.y += offsetV;
    sf::Vector2f offsetY = ball.v * dt;
    ball.pos += offsetY;
    updatePosBall(ball);
    ball.preTime = time;
}

void redrawFrame(sf::RenderWindow& window, circleName& ball)
{
    window.clear();
    window.draw(ball.circle);
    window.draw(ball.name);
    window.display();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Circle with name",
        sf::Style::Default,
        settings);

    circleName ball;
    init(ball);

    while (window.isOpen())
    {
        pollEvents(window);
        update(ball);
        redrawFrame(window, ball);
    }
}