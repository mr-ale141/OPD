#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#define OFFSET 10
#define WIDTH_ALPHA 190
#define HIGHT_ALPHA 300
#define WIDTH_LINE 5
#define WIDTH_SPACE 50
#define WINDOW_WIDTH WIDTH_ALPHA * 3 + WIDTH_SPACE * 2 + OFFSET * 2 + WIDTH_LINE
#define WINDOW_HIGHT HIGHT_ALPHA + 2 * OFFSET

void print_M(sf::RenderWindow * window, float x, float y) {
    sf::RectangleShape left_M;
    left_M.setSize({WIDTH_LINE, HIGHT_ALPHA});
    left_M.setPosition({x, y});
    left_M.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    (*window).draw(left_M);

    sf::RectangleShape left_iner_M;
    left_iner_M.setSize({WIDTH_LINE, WIDTH_ALPHA * 0.707});
    left_iner_M.setPosition({WIDTH_LINE + x, y});
    left_iner_M.setOrigin(WIDTH_LINE, 0);
    left_iner_M.setRotation(-45);
    left_iner_M.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    (*window).draw(left_iner_M);

    sf::RectangleShape right_iner_M;
    right_iner_M.setSize({WIDTH_LINE, WIDTH_ALPHA * 0.707});
    right_iner_M.setPosition({WIDTH_ALPHA + x, y});
    right_iner_M.setOrigin(0, 0);
    right_iner_M.setRotation(45);
    right_iner_M.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    (*window).draw(right_iner_M);

    sf::RectangleShape right_M;
    right_M.setSize({WIDTH_LINE, HIGHT_ALPHA});
    right_M.setPosition({WIDTH_ALPHA + x, y});
    right_M.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    (*window).draw(right_M);
}

void print_D(sf::RenderWindow *window, float x, float y) {
    sf::ConvexShape convex;
    convex.setOutlineThickness(WIDTH_LINE);
    convex.setOutlineColor(sf::Color(0xFF, 0xFF, 0xFF));
    convex.setFillColor(sf::Color(0x0, 0x0, 0x0));
    convex.setPointCount(12);
    convex.setPoint(0, {x + WIDTH_LINE, y + WIDTH_LINE});
    convex.setPoint(1, {WIDTH_ALPHA / 2 + x, WIDTH_LINE + y});

    convex.setPoint(2, {WIDTH_ALPHA / 2 + x + 4 * (WIDTH_ALPHA / 20), y + 1.5 * (HIGHT_ALPHA / 25)});
    convex.setPoint(3, {WIDTH_ALPHA / 2 + x + 7 * (WIDTH_ALPHA / 20), y + 3 * (HIGHT_ALPHA / 25)});
    convex.setPoint(4, {WIDTH_ALPHA / 2 + x + 9 * (WIDTH_ALPHA / 20), y + 6 * (HIGHT_ALPHA / 25)});
    convex.setPoint(5, {x + WIDTH_ALPHA, y + 10 * (HIGHT_ALPHA / 25)});
    convex.setPoint(6, {x + WIDTH_ALPHA, y + 15 * (HIGHT_ALPHA / 25)});
    convex.setPoint(7, {WIDTH_ALPHA / 2 + x + 9 * (WIDTH_ALPHA / 20), y + 19 * (HIGHT_ALPHA / 25)});
    convex.setPoint(8, {WIDTH_ALPHA / 2 + x + 7 * (WIDTH_ALPHA / 20), y + 22 * (HIGHT_ALPHA / 25)});
    convex.setPoint(9, {WIDTH_ALPHA / 2 + x + 4 * (WIDTH_ALPHA / 20), y + 23.5 * (HIGHT_ALPHA / 25)});

    convex.setPoint(10, {WIDTH_ALPHA / 2 + x, HIGHT_ALPHA + y - WIDTH_LINE});
    convex.setPoint(11, {x + WIDTH_LINE, HIGHT_ALPHA + y - WIDTH_LINE});
    (*window).draw(convex);
}

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HIGHT}), "Inicial");

    window.clear();

    print_M(&window, OFFSET, OFFSET);
    print_D(&window, OFFSET + WIDTH_ALPHA + WIDTH_SPACE, OFFSET);
    print_M(&window, OFFSET + 2 * WIDTH_SPACE + 2 * WIDTH_ALPHA, OFFSET);

    window.display();

    sf::sleep(sf::seconds(5));
}