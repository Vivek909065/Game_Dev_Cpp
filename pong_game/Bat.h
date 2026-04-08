#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bat
{
private:
    RectangleShape shape;
    float speed = 800.0f;
    float movement = 0;

public:
    Bat(float startX, float startY);

    FloatRect getPosition();
    RectangleShape getShape();

    void moveLeft();
    void moveRight();
    void stop();

    void update(Time dt);
};