#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({ 120, 300 }), "Rectangles and circle");

    window.clear();

    sf::RectangleShape base;
    base.setSize({100, 280});
    base.setPosition({10, 10});
    base.setFillColor(sf::Color(0x10, 0x10, 0x10));
    window.draw(base);

    sf::CircleShape green_lamp(40);
    green_lamp.setPosition({20, 20});
    green_lamp.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(green_lamp);

    sf::CircleShape ellow_lamp(40);
    ellow_lamp.setPosition({20, 110});
    ellow_lamp.setFillColor(sf::Color(0xFF, 0xFF, 0x0));
    window.draw(ellow_lamp);

    sf::CircleShape red_lamp(40);
    red_lamp.setPosition({20, 200});
    red_lamp.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(red_lamp);

    window.display();

    sf::sleep(sf::seconds(5));
}