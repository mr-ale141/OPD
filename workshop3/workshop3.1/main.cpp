// cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -S ./workshop1.1/ -B ./workshop1.1/
#include <SFML/Graphics.hpp>
#include <iostream>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

void initCircle(sf::CircleShape& circle)
{
    circle.setRadius(200);
    circle.setOrigin({ 200.f, 200.f });
    circle.setPosition({ 400.f, 300.f });
    circle.setFillColor(sf::Color(255, 150, 0));
    circle.setOutlineColor(sf::Color(0, 100, 255));
    circle.setOutlineThickness(5.f);
}

void initName(sf::Text& name, sf::Font& font)
{
    const char nameStr[] = "MDM";
    name.setFont(font);
    name.setString(nameStr);
    name.setCharacterSize(100);
    name.setFillColor(sf::Color(0, 0, 0));
    sf::Vector2f sizeName = name.getLocalBounds().getSize();
    name.setOrigin({ sizeName.x / 2, (float)(sizeName.y / 1.2) });
    name.setPosition({ 400.f, 300.f });
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

void update(sf::CircleShape& circle, sf::Text& name)
{
}

void redrawFrame(sf::RenderWindow& window, sf::CircleShape& circle, sf::Text& name)
{
    window.clear();
    window.draw(circle);
    window.draw(name);
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

    sf::CircleShape circle;
    initCircle(circle);

    sf::Font arial;
    arial.loadFromFile("arial.ttf");
    sf::Text name;
    initName(name, arial);

    while (window.isOpen())
    {
        pollEvents(window);
        update(circle, name);
        redrawFrame(window, circle, name);
    }
}