#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr int pointCount = 200;
constexpr float radiusMoving = 50.f;
constexpr float revPerSec = 1.f;

void setPositionRose(sf::ConvexShape *rose, sf::Vector2f position)
{
    rose->setPosition(position);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        const float roseRadius = 200 * std::sin(6 * angle);
        sf::Vector2f point = {
            roseRadius * std::sin(angle),
            roseRadius * std::cos(angle)};
        rose->setPoint(pointNo, point);
    }
}

int main()
{
    const sf::Vector2f centerMoving = {400.f, 300.f};
    constexpr float angleSpeed = revPerSec * (2 * M_PI);
    
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Rose",
        sf::Style::Default,
        settings);
    
    sf::Clock clock;
    
    sf::ConvexShape rose;
    rose.setFillColor(sf::Color(0xFF, 0x09, 0x80));
    rose.setPointCount(pointCount);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        const float time = clock.getElapsedTime().asSeconds();
        const float x = radiusMoving * std::cos(angleSpeed * time);
        const float y = radiusMoving * std::sin(angleSpeed * time);
        const sf::Vector2f offset = {x, y};
        setPositionRose(&rose, centerMoving + offset);
        window.clear();
        window.draw(rose);
        window.display();
    }
}