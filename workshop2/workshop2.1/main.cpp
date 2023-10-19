// cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -S ./workshop1.1/ -B ./workshop1.1/
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned BALL_SIZE = 50;

struct circleStruct
{
    sf::CircleShape circle;
    sf::Vector2f speed;
    float preTime;
};

sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        float(radius * std::cos(angle)),
        float(radius * std::sin(angle))
    };
}

float toDegress(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
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

void update(std::vector<circleStruct>& circles, sf::Clock& clock)
{
    for (int i = 0; i < std::size(circles); ++i)
    {
        float currTime = clock.getElapsedTime().asSeconds();
        float dt = currTime - circles[i].preTime;
        sf::Vector2f position = circles[i].circle.getPosition();
        position += circles[i].speed * dt;
        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (circles[i].speed.x > 0))
            circles[i].speed.x = -circles[i].speed.x;
        if ((position.x < 0) && (circles[i].speed.x < 0))
            circles[i].speed.x = -circles[i].speed.x;
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (circles[i].speed.y > 0))
            circles[i].speed.y = -circles[i].speed.y;
        if ((position.y < 0) && (circles[i].speed.y < 0))
            circles[i].speed.y = -circles[i].speed.y;
        circles[i].circle.setPosition(position);
        circles[i].preTime = currTime;
    }
}

void redrawFrame(sf::RenderWindow& window, std::vector<circleStruct>& circles)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    for (circleStruct circleItem : circles)
    {
        window.draw(circleItem.circle);
    }
    window.display();
}

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Cat moving",
        sf::Style::Default,
        settings);

    sf::CircleShape circleRed(BALL_SIZE);
    circleRed.setPosition({ 200, 120 });
    circleRed.setFillColor(sf::Color(0xFF, 0x00, 0x00));
    sf::CircleShape circleYellow(BALL_SIZE);
    circleYellow.setPosition({ 150, 200 });
    circleYellow.setFillColor(sf::Color(0xFF, 0xFF, 0x00));
    sf::CircleShape circleBlue(BALL_SIZE);
    circleBlue.setPosition({ 400, 450 });
    circleBlue.setFillColor(sf::Color(0x00, 0x00, 0xFF));
    sf::CircleShape circleGreen(BALL_SIZE);
    circleGreen.setPosition({ 350, 480 });
    circleGreen.setFillColor(sf::Color(0x00, 0xFF, 0x00));
    sf::CircleShape circleBlack(BALL_SIZE);
    circleBlack.setPosition({ 100, 50 });
    circleBlack.setFillColor(sf::Color(0x00, 0x00, 0x00));

    sf::Clock clock;

    std::vector<circleStruct> circles = {
        { circleRed, { 50.f, 75.f }, clock.getElapsedTime().asSeconds() },
        { circleYellow, { -50.f, -75.f }, clock.getElapsedTime().asSeconds() },
        { circleBlue, { 75.f, 50.f }, clock.getElapsedTime().asSeconds() },
        { circleGreen, { -75.f, -50.f }, clock.getElapsedTime().asSeconds() },
        { circleBlack, { 80.f, -60.f }, clock.getElapsedTime().asSeconds() }
    };

    while (window.isOpen())
    {
        pollEvents(window);
        update(circles, clock);
        redrawFrame(window, circles);
    }
}