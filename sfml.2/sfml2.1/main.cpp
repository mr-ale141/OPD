#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
int main()
{
    constexpr float BALL_SIZE = 40;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clock;
    sf::Vector2f position = {10, 260};
    float speedX = 150.f;
    float all_time = 0.0;
    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
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
        const float dtime = clock.restart().asSeconds();
        all_time += dtime;
        constexpr float amplitudeY = 80.f;
        constexpr float periodY = 2;
        const float wavePhase = all_time * float(2 * M_PI);
        const float x = speedX * dtime;
        const float y = amplitudeY * std::sin(wavePhase / periodY);
        const sf::Vector2f offset = {0, y};
        position.x += x;
        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedX > 0))
            speedX = -speedX;
        if ((position.x < 0) && (speedX < 0))
            speedX = -speedX;
        ball.setPosition(position + offset);
        window.clear();
        window.draw(ball);
        window.display();
    }
}