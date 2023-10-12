// cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -S ./workshop1.1/ -B ./workshop1.1/
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

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

void init(sf::ConvexShape& arrow)
{
    arrow.setPointCount(7);
    arrow.setPoint(0, { -40, -20 });
    arrow.setPoint(1, { 0, -20 });
    arrow.setPoint(2, { 0, -40 });
    arrow.setPoint(3, { 40, 0 });
    arrow.setPoint(4, { 0, 40 });
    arrow.setPoint(5, { 0, 20 });
    arrow.setPoint(6, { -40, 20 });
    arrow.setPosition({ 400, 300 });
    arrow.setFillColor(sf::Color(0xFF, 0xFF, 0x00));
    arrow.setRotation(10.0f);
    arrow.setOutlineColor(sf::Color(0x00, 0x00, 0x00));
    arrow.setOutlineThickness(2.0f);
}

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
    mousePosition = { float(event.x), float(event.y) };
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void updateAngleArrow(float preTime[2], const sf::Vector2f& mousePosition, sf::ConvexShape& arrow, sf::Clock& clock)
{
    constexpr float angleSpeed = 15.f;
    const float time = clock.getElapsedTime().asSeconds();
    const float dTime = time - preTime[1];
    preTime[1] = time;
    const sf::Vector2f newRadiusVector = mousePosition - arrow.getPosition();
    float mouseAngle = toDegress(atan2(newRadiusVector.y, newRadiusVector.x));
    const float pointerAngle = arrow.getRotation();
    mouseAngle = (mouseAngle < 0) ? 360 + mouseAngle : mouseAngle;
    if (mouseAngle != pointerAngle)
    {
        float deltaAngle = mouseAngle - pointerAngle;
        float unsignedAngleOffset = dTime * angleSpeed;
        float signedOffset = (deltaAngle > 0 && deltaAngle < 180 || deltaAngle < 0 && deltaAngle < -180) ? 1 : -1;
        float angleOffset = unsignedAngleOffset * signedOffset;
        arrow.rotate((std::abs(angleOffset) > std::abs(deltaAngle)) ? deltaAngle : angleOffset);
    }
}

void updatePositionArrow(float preTime[2], const sf::Vector2f& mousePosition, sf::ConvexShape& arrow, sf::Clock& clock)
{
    constexpr float speed = 20.f;
    const float time = clock.getElapsedTime().asSeconds();
    const float dTime = time - preTime[0];
    preTime[0] = time;
    const sf::Vector2f arrowPos = arrow.getPosition();
    const sf::Vector2f offset = mousePosition - arrowPos;
    if (offset.x != 0 && offset.y != 0)
    {
        const float dist = std::abs(std::sqrt(offset.x * offset.x + offset.y * offset.y));
        const sf::Vector2f normOffset = { offset.x / dist, offset.y / dist };
        const float stepLen = speed * dTime;
        const sf::Vector2f mov = { normOffset.x * stepLen, normOffset.y * stepLen };
        arrow.setPosition(arrowPos + mov);
    }
}

void update(float preTime[2], const sf::Vector2f& mousePosition, sf::ConvexShape& arrow, sf::Clock& clock)
{
    updateAngleArrow(preTime, mousePosition, arrow, clock);
    updatePositionArrow(preTime, mousePosition, arrow, clock);
}

void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& arrow)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(arrow);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    float preTime[2];

    sf::Clock clock;
    preTime[0] = clock.getElapsedTime().asSeconds();
    preTime[1] = clock.getElapsedTime().asSeconds();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Arrow moving",
        sf::Style::Default,
        settings);

    sf::ConvexShape arrow;
    sf::Vector2f mousePosition;

    init(arrow);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(preTime, mousePosition, arrow, clock);
        redrawFrame(window, arrow);
    }
}