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
constexpr unsigned BALL_SIZE = 50;
constexpr unsigned MIN_BALL_COUNT = 2;
constexpr unsigned MAX_BALL_COUNT = 10;
constexpr float MIN_SPEED = 80.f;
constexpr float MAX_SPEED = 180.f;
constexpr float LIFE_TIME = 10.f;

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

float dot(sf::Vector2f speed, sf::Vector2f pos)
{
    return speed.x * pos.x + speed.y * pos.y;
}

float getModule(sf::Vector2f v)
{
    float module = std::sqrt(v.x * v.x + v.y * v.y);
    if (module == 0)
        module = 0.000001;
    return module;
}

void updateSpeedAfterImpact(sf::Vector2f& v1, sf::Vector2f c1, sf::Vector2f& v2, sf::Vector2f c2)
{

    sf::Vector2f w1 = v1 - (dot(v1 - v2, c1 - c2) / (getModule(c1 - c2) * getModule(c1 - c2))) * (c1 - c2);
    sf::Vector2f w2 = v2 - (dot(v2 - v1, c2 - c1) / (getModule(c2 - c1) * getModule(c2 - c1))) * (c2 - c1);
    v1 = w1;
    v2 = w2;
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
    sf::CircleShape circle(BALL_SIZE);
    circle.setFillColor(sf::Color(getRandomInt(generator, 0, 255), getRandomInt(generator, 0, 255), getRandomInt(generator, 0, 255)));
    circle.setOrigin({ BALL_SIZE, BALL_SIZE });
    sf::Vector2f position;
    bool isBusyPosition;
    int count = 0;
    do
    {
        count++;
        isBusyPosition = false;
        position = { getRandomFloat(generator, BALL_SIZE, WINDOW_WIDTH - BALL_SIZE), getRandomFloat(generator, BALL_SIZE, WINDOW_HEIGHT - BALL_SIZE) };
        for (int i = 0; i < circles.size(); ++i)
            if (getModule(circles[i].circle.getPosition() - position) < 2 * BALL_SIZE)
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
        if ((position.x + BALL_SIZE >= WINDOW_WIDTH) && (circles[i].speed.x > 0))
            circles[i].speed.x = -circles[i].speed.x;
        if ((position.x - BALL_SIZE < 0) && (circles[i].speed.x < 0))
            circles[i].speed.x = -circles[i].speed.x;
        if ((position.y + BALL_SIZE >= WINDOW_HEIGHT) && (circles[i].speed.y > 0))
            circles[i].speed.y = -circles[i].speed.y;
        if ((position.y - BALL_SIZE < 0) && (circles[i].speed.y < 0))
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
                sf::Vector2f dPos = posI - posJ;
                float dist = getModule(dPos);
                if (dist < 2 * BALL_SIZE)
                {
                    updateSpeedAfterImpact(circles[i].speed, posI, circles[j].speed, posJ);
                }
            }
}

void update(std::vector<circleStruct>& circles, sf::Clock& clock, float& preTimeFrame)
{
    constexpr float freqFrame = 60.f;
    constexpr float lenOneFrame = 1.f / freqFrame;
    constexpr int countSetPhisic = 50;
    constexpr float lenOneSet = lenOneFrame / countSetPhisic;
    int count = 0;
    float time = clock.getElapsedTime().asSeconds();
    if (count == 0) preTimeFrame = time;
    if (time - preTimeFrame >= lenOneSet * count)
    {
        removeDeathBalls(circles);
        checkBetweenBallImpacts(circles);
        checkWallImpacts(circles, clock);
        count++;
        if (count == countSetPhisic) count = 0;
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
    float preTimeFrame;
    std::vector<circleStruct> circles;

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
        update(circles, clock, preTimeFrame);
        redrawFrame(window, circles);
    }
}