// cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -S ./workshop1.1/ -B ./workshop1.1/
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned MIN_BALL_COUNT = 2;
constexpr unsigned MAX_BALL_COUNT = 10;
constexpr float MIN_BALL_SIZE = 20;
constexpr float MAX_BALL_SIZE = 70;
constexpr float MIN_SPEED = 180.f;
constexpr float MAX_SPEED = 250.f;
constexpr float LIFE_TIME = 10.f;
constexpr float DENSITY = 1.5f;
constexpr float TOLERANCE = 0.01f;

struct PRNG
{
    std::mt19937 engine;
};

struct circleStruct
{
    sf::CircleShape circle;
    sf::Vector2f speed;
    float preTime;
    float liveTime;
};

void initGenerator(PRNG& generator)
{
    std::random_device device;
    generator.engine.seed(device());
}

unsigned getRandomInt(PRNG& generator, unsigned minValue, unsigned maxValue)
{
    assert(minValue < maxValue);
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

float getRandomFloat(PRNG& generator, float minValue, float maxValue)
{
    assert(minValue < maxValue);
    std::uniform_real_distribution<float> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

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

float dot(sf::Vector2f v1, sf::Vector2f v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

float getModule(sf::Vector2f v)
{
    float module = std::sqrt(v.x * v.x + v.y * v.y);
    // if (module == 0)
    //     module = 0.000001;
    return module;
}

bool areCloseAbsolute(float a, float b, float tolerance = 0.001f)
{
    return std::abs(a - b) < tolerance;
}

bool areCloseRelative(float a, float b, float tolerance = 0.001f)
{
    return std::abs((a - b) / b) < tolerance;
}

bool areFuzzyEqual(float a, float b)
{
    float tolerance = TOLERANCE;
    if (std::abs(b) > 1.f)
    {
        return areCloseRelative(a, b, tolerance);
    }
    return areCloseAbsolute(a, b, tolerance);
}

void updateSpeedAfterImpact(circleStruct& circle1, circleStruct& circle2)
{
    // float r1 = circle1.circle.getRadius();
    // float r2 = circle2.circle.getRadius();
    // float m1 = DENSITY * r1 * r1 * r1;
    // float m2 = DENSITY * r2 * r2 * r2;
    sf::Vector2f v1 = circle1.speed;
    sf::Vector2f v2 = circle2.speed;
    // float modV1 = getModule(v1);
    // float modV2 = getModule(v2);
    sf::Vector2f c1 = circle1.circle.getPosition();
    sf::Vector2f c2 = circle2.circle.getPosition();
    sf::Vector2f w1 = v1 - (dot(v1 - v2, c1 - c2) / (getModule(c1 - c2) * getModule(c1 - c2))) * (c1 - c2);
    sf::Vector2f w2 = v2 - (dot(v2 - v1, c2 - c1) / (getModule(c2 - c1) * getModule(c2 - c1))) * (c2 - c1);
    // float modW1 = getModule(w1);
    // float modW2 = getModule(w2);
    // assert(areFuzzyEqual(getModule(v1 + v2), getModule(w1 + w2)));
    circle1.speed = w1;
    circle2.speed = w2;
    // float Ev1 = m1 * modV1 * modV1;
    // float Ev2 = m2 * modV2 * modV2;
    // float Ew1 = m1 * modW1 * modW1;
    // float Ew2 = m2 * modW2 * modW2;
    // float Pv1 = m1 * modV1;
    // float Pv2 = m2 * modV2;
    // float Pw1 = m1 * modW1;
    // float Pw2 = m2 * modW2;
    // std::cout << modV1 + modV2 << std::endl;
    // std::cout << modW1 + modW2 << std::endl;
    // std::cout << std::endl;
    // std::cout << Ev1 + Ev2 << std::endl;
    // std::cout << Ew1 + Ew2 << std::endl;
    // std::cout << std::endl;
    // std::cout << Pv1 + Pv2 << std::endl;
    // std::cout << Pw1 + Pw2 << std::endl;
    // std::cout << std::endl;
    // assert(areFuzzyEqual(Ev1 + Ev2, Ew1 + Ew2));
    // assert(areFuzzyEqual(Pv1 + Pv2, Pw1 + Pw2));
}

void createRandomBall(std::vector<circleStruct>& circles, PRNG& generator, sf::Clock& clock)
{
    circleStruct circleItm;
    sf::Vector2f speed;
    if (getRandomInt(generator, 0, 1))
        speed.x = getRandomFloat(generator, MIN_SPEED, MAX_SPEED);
    else
        speed.x = -getRandomFloat(generator, MIN_SPEED, MAX_SPEED);
    if (getRandomInt(generator, 0, 1))
        speed.y = getRandomFloat(generator, MIN_SPEED, MAX_SPEED);
    else
        speed.y = -getRandomFloat(generator, MIN_SPEED, MAX_SPEED);
    // float sizeBall = getRandomFloat(generator, MIN_BALL_SIZE, MAX_BALL_SIZE);
    float radiusBall = 50.f;
    sf::CircleShape circle;
    circle.setRadius(radiusBall);
    circle.setFillColor(sf::Color(getRandomInt(generator, 0, 255), getRandomInt(generator, 0, 255), getRandomInt(generator, 0, 255)));
    circle.setOrigin({ radiusBall, radiusBall });
    sf::Vector2f position;
    bool isBusyPosition;
    int count = 0;
    do
    {
        count++;
        isBusyPosition = false;
        position = { getRandomFloat(generator, radiusBall, WINDOW_WIDTH - radiusBall), getRandomFloat(generator, radiusBall, WINDOW_HEIGHT - radiusBall) };
        for (int i = 0; i < circles.size(); ++i)
            if (getModule(circles[i].circle.getPosition() - position) < radiusBall + circles[i].circle.getRadius())
                isBusyPosition = true;
    } while (isBusyPosition && count < 1000);
    if (count < 1000)
    {
        circle.setPosition(position);
        circleItm.circle = circle;
        circleItm.speed = speed;
        circleItm.preTime = clock.getElapsedTime().asSeconds();
        circleItm.liveTime = LIFE_TIME;
        circles.push_back(circleItm);
    }
}

bool isDeth(circleStruct circleItm)
{
    return (circleItm.liveTime <= 0);
}

void removeDeathBalls(std::vector<circleStruct>& circles)
{
    if (circles.size() != 0)
    {
        auto newEnd = std::remove_if(circles.begin(), circles.end(), isDeth);
        circles.erase(newEnd, circles.end());
    }
}

void pollEvents(sf::RenderWindow& window, std::vector<circleStruct>& circles, PRNG& generator, sf::Clock& clock)
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
            createRandomBall(circles, generator, clock);
            break;
        default:
            break;
        }
    }
}

void checkWallImpacts(std::vector<circleStruct>& circles, sf::Clock& clock)
{
    for (int i = 0; i < std::size(circles); ++i)
    {
        float currTime = clock.getElapsedTime().asSeconds();
        float dt = currTime - circles[i].preTime;
        circles[i].liveTime -= dt;
        sf::Vector2f position = circles[i].circle.getPosition();
        position += circles[i].speed * dt;
        float r = circles[i].circle.getRadius();
        if ((position.x + r >= WINDOW_WIDTH) && (circles[i].speed.x > 0))
            circles[i].speed.x = -circles[i].speed.x;
        if ((position.x - r < 0) && (circles[i].speed.x < 0))
            circles[i].speed.x = -circles[i].speed.x;
        if ((position.y + r >= WINDOW_HEIGHT) && (circles[i].speed.y > 0))
            circles[i].speed.y = -circles[i].speed.y;
        if ((position.y - r < 0) && (circles[i].speed.y < 0))
            circles[i].speed.y = -circles[i].speed.y;
        circles[i].circle.setPosition(position);
        circles[i].preTime = currTime;
    }
}

void checkBetweenBallImpacts(std::vector<circleStruct>& circles)
{
    if (circles.size() > 1)
        for (int i = 0; i < std::size(circles); ++i)
            for (int j = i + 1; j < std::size(circles); ++j)
            {
                sf::Vector2f posI = circles[i].circle.getPosition();
                sf::Vector2f posJ = circles[j].circle.getPosition();
                float r1 = circles[i].circle.getRadius();
                float r2 = circles[j].circle.getRadius();
                sf::Vector2f dPos = posI - posJ;
                float dist = getModule(dPos);
                if (dist < r1 + r2)
                {
                    updateSpeedAfterImpact(circles[i], circles[j]);
                }
            }
}

void update(std::vector<circleStruct>& circles, sf::Clock& clock)
{
    constexpr float freqFrame = 50.f;
    constexpr float lenOneFrame = 1.f / freqFrame;
    float time = clock.getElapsedTime().asSeconds();
    float preTime = time;
    while (time - preTime < lenOneFrame)
    {
        removeDeathBalls(circles);
        checkBetweenBallImpacts(circles);
        checkWallImpacts(circles, clock);
        time = clock.getElapsedTime().asSeconds();
    }
}

void redrawFrame(sf::RenderWindow& window, std::vector<circleStruct>& circles)
{
    window.clear();
    for (circleStruct circleItem : circles)
    {
        window.draw(circleItem.circle);
    }
    window.display();
}

int main()
{
    PRNG generator;
    initGenerator(generator);
    sf::Clock clock;
    std::vector<circleStruct> circles;
    float preTime = clock.getElapsedTime().asSeconds();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
        "Ball moving",
        sf::Style::Default,
        settings);

    while (window.isOpen())
    {
        pollEvents(window, circles, generator, clock);
        update(circles, clock);
        redrawFrame(window, circles);
    }
}