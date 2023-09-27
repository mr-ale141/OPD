#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr int pointCount = 200;

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
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Ellipse",
        sf::Style::Default,
        settings);
    sf::ConvexShape rose;
    rose.setFillColor(sf::Color(0xFF, 0x09, 0x80));
    rose.setPointCount(pointCount);
    setPositionRose(&rose, {400, 320});
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
        window.clear();
        window.draw(rose);
        window.display();
    }
}