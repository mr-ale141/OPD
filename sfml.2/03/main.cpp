#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
int main()
{
    constexpr int pointCount = 200;
    const sf::Vector2f ellipseRadius = {200.f, 80.f};
    //создаем окно с параметрами сглаживания
    /*
    воспользуемся специальным конструктором sf::RenderWindow, который принимает параметры 
    в виде sf::ContextSettings.В эти параметры мы добавим antialiasingLevel, что обеспечит 
    нам автоматическое сглаживание(antialiasing) краёв фигур за счёт рисования промежуточных 
    полупрозрачных цветов на краях.
    */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Ellipse",
        sf::Style::Default,
        settings
    );
    //создаем элипс
    sf::ConvexShape ellipse;
    ellipse.setPosition({400, 320});
    ellipse.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    //инициализируем вершины елипса
    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)
        };
        ellipse.setPoint(pointNo, point);
    }
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
        window.draw(ellipse);
        window.display();
    }
}
