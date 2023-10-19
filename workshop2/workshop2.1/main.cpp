// cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -S ./workshop1.1/ -B ./workshop1.1/
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        float(radius * std::cos(angle)),
        float(radius * std::sin(angle))
    };
}

float toDegress(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseClick(const sf::Event::MouseButtonEvent& event, sf::Vector2f& mousePositionClick)
{
    mousePositionClick = { float(event.x), float(event.y) };
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePositionClick, bool& caught)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            caught = false;
            onMouseClick(event.mouseButton, mousePositionClick);
            break;
        default:
            break;
        }
    }
}

void updateAngleСat(float preTime[2], const sf::Vector2f& mousePositionClick, sf::Sprite& cat, sf::Clock& clock)
{
    if ((mousePositionClick.x - cat.getPosition().x) < 0)
        cat.setScale(-1, 1);
    else
        cat.setScale(1, 1);
}

void updatePositionСat(
    bool& caught,
    float preTime[2],
    const sf::Vector2f& mousePositionClick,
    sf::Sprite& cat,
    sf::Clock& clock)
{
    constexpr float speed = 20.f;
    const float time = clock.getElapsedTime().asSeconds();
    const float dTime = time - preTime[0];
    preTime[0] = time;
    const sf::Vector2f catPos = cat.getPosition();
    const sf::Vector2f offset = mousePositionClick - catPos;
    if (offset.x != 0 && offset.y != 0)
    {
        const float dist = std::abs(std::sqrt(offset.x * offset.x + offset.y * offset.y));
        const sf::Vector2f normOffset = { offset.x / dist, offset.y / dist };
        const float stepLen = speed * dTime;
        const sf::Vector2f mov = { normOffset.x * stepLen, normOffset.y * stepLen };
        cat.setPosition(catPos + mov);
    }
    else
        caught = true;
}

void update(
    bool& caught,
    float preTime[2],
    const sf::Vector2f& mousePositionClick,
    sf::Sprite& cat,
    sf::Sprite& redPointer,
    sf::Clock& clock)
{
    redPointer.setPosition(mousePositionClick);
    if (caught == false)
    {
        updateAngleСat(preTime, mousePositionClick, cat, clock);
        updatePositionСat(caught, preTime, mousePositionClick, cat, clock);
    }
    else
    {
        preTime[0] = clock.getElapsedTime().asSeconds();
        preTime[1] = clock.getElapsedTime().asSeconds();
    }
}

void redrawFrame(sf::RenderWindow& window, sf::Sprite& cat, sf::Sprite& redPint, bool caught)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(cat);
    if (caught == false)
        window.draw(redPint);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    float preTime[2];

    sf::Clock clock;
    preTime[0] = clock.getElapsedTime().asSeconds();
    preTime[1] = clock.getElapsedTime().asSeconds();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Cat moving",
        sf::Style::Default,
        settings);

    sf::Texture textureCat;
    if (!textureCat.loadFromFile("cat.png"))
    {
        return 1;
    }
    sf::Texture textureRedPoint;
    if (!textureRedPoint.loadFromFile("red_pointer.png"))
    {
        return 1;
    }

    sf::Sprite cat;
    cat.setTexture(textureCat);
    cat.setOrigin({ 19.f, 12.f });
    cat.setPosition({ 400, 300 });
    sf::Sprite redPoint;
    redPoint.setTexture(textureRedPoint);
    redPoint.setOrigin({ 16.f, 16.f });
    bool caught = true;
    sf::Vector2f mousePositionClick;

    while (window.isOpen())
    {
        pollEvents(window, mousePositionClick, caught);
        update(caught, preTime, mousePositionClick, cat, redPoint, clock);
        redrawFrame(window, cat, redPoint, caught);
    }
}