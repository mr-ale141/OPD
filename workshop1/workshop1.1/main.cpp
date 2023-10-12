// cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -S ./workshop1.1/ -B ./workshop1.1/
// F10 переход через инструкцию
// F11 заход в тело вызываемой функции
// Shift + F11 выход из тела вызываемой функции
// F5 продолжение выполнения до следующей точки останова либо до завершения программы
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void init(sf::ConvexShape& arrow)
{
    arrow.setPointCount(7);
    arrow.setPoint(0, { -20, 0 });
    arrow.setPoint(1, { -40, 0 });
    arrow.setPoint(2, { 0, -40 });
    arrow.setPoint(3, { 40, 0 });
    arrow.setPoint(4, { 20, 0 });
    arrow.setPoint(5, { 20, 40 });
    arrow.setPoint(6, { -20, 40 });
    arrow.setPosition({ 400, 300 });
    arrow.setFillColor(sf::Color(0xFF, 0xFF, 0x00));
    arrow.setRotation(10.0f);
    arrow.setOutlineColor(sf::Color(0x00, 0x00, 0x00));
    arrow.setOutlineThickness(2.0f);
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

void update(sf::ConvexShape& arrow)
{
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

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Arrow",
        sf::Style::Default,
        settings);

    sf::ConvexShape arrow;

    init(arrow);

    while (window.isOpen())
    {
        pollEvents(window);
        update(arrow);
        redrawFrame(window, arrow);
    }
}