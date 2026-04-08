#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
private:
    CircleShape shape;
    float xVelocity = 400.0f;
    float yVelocity = 400.0f;

public:
    Ball(float startX, float startY);

    FloatRect getPosition();
    CircleShape getShape();
    float getSize();

    void reboundSides();
    void reboundBatOrTop();
    void reboundBottom();

    void update(Time dt);

    // For collision fix
    void setPosition(Vector2f pos);
};