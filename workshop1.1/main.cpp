// cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ./workshop1.1
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void init(sf::ConvexShape& pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, { 40, 0 });
    pointer.setPoint(1, { -20, -20 });
    pointer.setPoint(2, { -20, 20 });
    pointer.setPosition({ 400, 300 });
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

float toDegress(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
    // std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
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

void update(const sf::Vector2f& mousePosition, sf::ConvexShape& pointer, sf::Clock& clock)
{
    constexpr float angleSpeed = 15.f;
    const float dtime = clock.restart().asSeconds();
    const sf::Vector2f newRadiusVector = mousePosition - pointer.getPosition();
    float mouseAngle = toDegress(atan2(newRadiusVector.y, newRadiusVector.x));
    const float pointerAngle = pointer.getRotation();
    mouseAngle = (mouseAngle < 0) ? 360 + mouseAngle : mouseAngle;
    if (mouseAngle != pointerAngle)
    {
        float deltaAngle = mouseAngle - pointerAngle;
        float unsignedAngleOffset = dtime * angleSpeed;
        float signedOffset = (deltaAngle > 0 && deltaAngle < 180 || deltaAngle < 0 && deltaAngle < -180) ? 1 : -1;
        float angleOffset = unsignedAngleOffset * signedOffset;
        pointer.rotate((std::abs(angleOffset) > std::abs(deltaAngle)) ? deltaAngle : angleOffset);
    }
}

void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::Clock clock;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Pointer follows mouse",
        sf::Style::Default,
        settings);

    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;

    init(pointer);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, pointer, clock);
        redrawFrame(window, pointer);
    }
}