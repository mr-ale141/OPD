#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HIGHT 600

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HIGHT}), "House");

    window.clear();

    sf::RectangleShape blockHouse;
    blockHouse.setPosition({WINDOW_WIDTH / 10, WINDOW_HIGHT / 2});
    blockHouse.setSize({WINDOW_WIDTH - 2 * WINDOW_WIDTH / 10, WINDOW_HIGHT / 2 - WINDOW_HIGHT / 15});
    blockHouse.setFillColor(sf::Color(0x42, 0x25, 0x0B));
    window.draw(blockHouse);

    sf::RectangleShape door;
    door.setPosition({2 * WINDOW_WIDTH / 10, WINDOW_HIGHT - WINDOW_HIGHT / 15});
    door.setSize({WINDOW_WIDTH / 9, -WINDOW_HIGHT / 3});
    door.setFillColor(sf::Color(0x10, 0x10, 0x10));
    window.draw(door); 

    sf::ConvexShape roof;
    roof.setFillColor(sf::Color(0x59, 0x23, 0x21));
    roof.setPosition({WINDOW_WIDTH / 2, WINDOW_HIGHT / 2});
    roof.setPointCount(4);
    roof.setPoint(0, {-WINDOW_WIDTH / 2 + WINDOW_WIDTH / 80, 0});
    roof.setPoint(1, {-WINDOW_WIDTH / 4, -WINDOW_HIGHT / 4 + WINDOW_HIGHT / 60});
    roof.setPoint(2, {WINDOW_WIDTH / 4, -WINDOW_HIGHT / 4 + WINDOW_HIGHT / 60});
    roof.setPoint(3, {WINDOW_WIDTH / 2 - WINDOW_WIDTH / 80, 0});
    window.draw(roof);

    sf::RectangleShape tube;
    tube.setPosition({3 * WINDOW_WIDTH / 4 - WINDOW_WIDTH / 70, WINDOW_HIGHT / 4});
    tube.setSize({-WINDOW_WIDTH / 16 + 2 * WINDOW_WIDTH / 70, WINDOW_HIGHT / 8});
    tube.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(tube);

    sf::CircleShape smouke1(WINDOW_HIGHT / 40);
    smouke1.setFillColor(sf::Color(0xD7, 0xD7, 0xD7));
    smouke1.setPosition({3 * WINDOW_WIDTH / 4 - 2 * WINDOW_HIGHT / 40, 3 * WINDOW_HIGHT / 16 - 2 * WINDOW_HIGHT / 45});
    window.draw(smouke1);

    sf::CircleShape smouke2(WINDOW_HIGHT / 45);
    smouke2.setFillColor(sf::Color(0xD7, 0xD7, 0xD7));
    smouke2.setPosition({3 * WINDOW_WIDTH / 4, 3 * WINDOW_HIGHT / 16 - 3 * WINDOW_HIGHT / 45});
    window.draw(smouke2);

    sf::CircleShape smouke3(WINDOW_HIGHT / 40);
    smouke3.setFillColor(sf::Color(0xD7, 0xD7, 0xD7));
    smouke3.setPosition({3 * WINDOW_WIDTH / 4 - 2 * WINDOW_HIGHT / 40, 3 * WINDOW_HIGHT / 16 - 2 * WINDOW_HIGHT / 45});
    window.draw(smouke3);

    sf::CircleShape smouke4(WINDOW_HIGHT / 40);
    smouke4.setFillColor(sf::Color(0xD7, 0xD7, 0xD7));
    smouke4.setPosition({3 * WINDOW_WIDTH / 4 - 2 * WINDOW_HIGHT / 40, 3 * WINDOW_HIGHT / 16 - 2 * WINDOW_HIGHT / 45});
    window.draw(smouke4);

    sf::RectangleShape cap;
    cap.setPosition({3 * WINDOW_WIDTH / 4, WINDOW_HIGHT / 4});
    cap.setSize({-WINDOW_WIDTH / 16, -WINDOW_HIGHT / 16});
    cap.setFillColor(sf::Color(0x80, 0x80, 0x80));
    window.draw(cap);


    window.display();

    sf::sleep(sf::seconds(5));
}