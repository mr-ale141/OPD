// cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -S ./workshop1.1/ -B ./workshop1.1/
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned BALL_SIZE = 50;
int count = 0;

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

float dot(sf::Vector2f speed, sf::Vector2f pos)
{
    return speed.x * pos.x + speed.y * pos.y;
}

float getModule(sf::Vector2f v)
{
    float module = std::sqrt(v.x * v.x + v.y * v.y);
    if (module == 0)
        module = 0.000001;
    return module;
}

void updateSpeedAfterImpact(sf::Vector2f& v1, sf::Vector2f c1, sf::Vector2f& v2, sf::Vector2f c2)
{

    sf::Vector2f w1 = v1 - (dot(v1 - v2, c1 - c2) / (getModule(c1 - c2) * getModule(c1 - c2))) * (c1 - c2);
    sf::Vector2f w2 = v2 - (dot(v2 - v1, c2 - c1) / (getModule(c2 - c1) * getModule(c2 - c1))) * (c2 - c1);
    v1 = w1;
    v2 = w2;
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
        if ((position.x + BALL_SIZE >= WINDOW_WIDTH) && (circles[i].speed.x > 0))
            circles[i].speed.x = -circles[i].speed.x;
        if ((position.x - BALL_SIZE < 0) && (circles[i].speed.x < 0))
            circles[i].speed.x = -circles[i].speed.x;
        if ((position.y + BALL_SIZE >= WINDOW_HEIGHT) && (circles[i].speed.y > 0))
            circles[i].speed.y = -circles[i].speed.y;
        if ((position.y - BALL_SIZE < 0) && (circles[i].speed.y < 0))
            circles[i].speed.y = -circles[i].speed.y;
        circles[i].circle.setPosition(position);
        circles[i].preTime = currTime;
    }
    for (int i = 0; i < std::size(circles); ++i)
        for (int j = i + 1; j < std::size(circles); ++j)
        {
            sf::Vector2f posI = circles[i].circle.getPosition();
            sf::Vector2f posJ = circles[j].circle.getPosition();
            sf::Vector2f dPos = posI - posJ;
            float dist = getModule(dPos);
            if (dist <= 2 * BALL_SIZE)
            {
                updateSpeedAfterImpact(circles[i].speed, posI, circles[j].speed, posJ);
            }
        }
}

void redrawFrame(sf::RenderWindow& window, std::vector<circleStruct>& circles)
{
    window.clear();
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
    circleRed.setOrigin({ BALL_SIZE, BALL_SIZE });
    sf::CircleShape circleYellow(BALL_SIZE);
    circleYellow.setPosition({ 500, 200 });
    circleYellow.setFillColor(sf::Color(0xFF, 0xFF, 0x00));
    circleYellow.setOrigin({ BALL_SIZE, BALL_SIZE });
    sf::CircleShape circleBlue(BALL_SIZE);
    circleBlue.setPosition({ 200, 450 });
    circleBlue.setFillColor(sf::Color(0x00, 0x00, 0xFF));
    circleBlue.setOrigin({ BALL_SIZE, BALL_SIZE });
    sf::CircleShape circleGreen(BALL_SIZE);
    circleGreen.setPosition({ 350, 480 });
    circleGreen.setFillColor(sf::Color(0x00, 0xFF, 0x00));
    circleGreen.setOrigin({ BALL_SIZE, BALL_SIZE });
    sf::CircleShape circleBlack(BALL_SIZE);
    circleBlack.setPosition({ 100, 50 });
    circleBlack.setFillColor(sf::Color(0x00, 0xFF, 0xFF));
    circleBlack.setOrigin({ BALL_SIZE, BALL_SIZE });

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