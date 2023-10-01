// cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug .
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Eye
{
    const sf::Vector2f radiusEyeball = {40.f, 100.f};
    const sf::Vector2f radiusPupil = {10.f, 25.f};
    const sf::Vector2f radiusMuving = {20.f, 50.f};
    const int pointCountBall = 200;
    const int pointCountPupil = 100;
    sf::ConvexShape eyeball;
    sf::ConvexShape pupil;
    bool mouseInEye = false;
    float angleLooking = 0.f;
    sf::Vector2f positionMouseInEye = {0.f, 0.f};
};

struct Face
{
    const sf::Vector2f positionLeftEye = {320.f, 300.f};
    const sf::Vector2f positionRightEye = {440.f, 300.f};
    Eye leftEye;
    Eye rightEye;
};

sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        float(radius * std::cos(angle)),
        float(radius * std::sin(angle))
    };
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void updateEyeElements(Eye &eye)
{
    if (eye.mouseInEye)
        eye.pupil.setPosition(eye.eyeball.getPosition() + eye.positionMouseInEye);
    else
    {
        sf::Vector2f pupilPositionOffset = {
            eye.radiusMuving.x * std::cos(eye.angleLooking),
            eye.radiusMuving.y * std::sin(eye.angleLooking)
        };
        eye.pupil.setPosition(eye.eyeball.getPosition() + pupilPositionOffset);
    }
}

void initEye(Eye &eye, sf::Vector2f position)
{
    eye.eyeball.setPosition(position);
    eye.eyeball.setPointCount(eye.pointCountBall);
    eye.eyeball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    for (int i = 0; i < eye.pointCountBall; ++i)
    {
        float angle = float(2 * M_PI * i) / float(eye.pointCountBall);
        sf::Vector2f point = {
            eye.radiusEyeball.x * std::sin(angle),
            eye.radiusEyeball.y * std::cos(angle)
        };
        eye.eyeball.setPoint(i, point);
    }

    eye.pupil.setPointCount(eye.pointCountPupil);
    eye.pupil.setFillColor(sf::Color(0x00, 0x00, 0x00));
    for (int i = 0; i < eye.pointCountPupil; ++i)
    {
        float angle = float(2 * M_PI * i) / float(eye.pointCountPupil);
        sf::Vector2f point = {
            eye.radiusPupil.x * std::sin(angle),
            eye.radiusPupil.y * std::cos(angle)};
        eye.pupil.setPoint(i, point);
    }

    updateEyeElements(eye);
}

void initFace(Face &face)
{
    initEye(face.leftEye, face.positionLeftEye);
    initEye(face.rightEye, face.positionRightEye);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    //std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void updateEye(const sf::Vector2f &mousePosition, Eye &eye)
{
    const sf::Vector2f delta = mousePosition - eye.eyeball.getPosition();
    eye.angleLooking = atan2(delta.y, delta.x);
    std::cout << "angleLooking=" << eye.angleLooking << std::endl;
    updateEyeElements(eye);
}

void redrawFrame(sf::RenderWindow &window, Face &face)
{
    window.clear();
    window.draw(face.leftEye.eyeball);
    window.draw(face.leftEye.pupil);
    window.draw(face.rightEye.eyeball);
    window.draw(face.rightEye.pupil);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    sf::Vector2f mousePosition;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Eye follows mouse",
        sf::Style::Default,
        settings);

    Face face;
    initFace(face);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        updateEye(mousePosition, face.leftEye);
        updateEye(mousePosition, face.rightEye);
        redrawFrame(window, face);
    }
}