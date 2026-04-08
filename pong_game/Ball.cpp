#include "Ball.h"
#include <cstdlib>

Ball::Ball(float startX, float startY)
{
    shape.setRadius(10);
    shape.setFillColor(Color::White);
    shape.setPosition(startX, startY);

    if (rand() % 2 == 0)
        xVelocity = -xVelocity;
}

FloatRect Ball::getPosition()
{
    return shape.getGlobalBounds();
}

CircleShape Ball::getShape()
{
    return shape;
}

float Ball::getSize()
{
    return shape.getRadius() * 2;
}

void Ball::reboundSides()
{
    xVelocity = -xVelocity;
}

void Ball::reboundBatOrTop()
{
    yVelocity = -yVelocity;
}

void Ball::reboundBottom()
{
    shape.setPosition(500, 0);
}

void Ball::update(Time dt)
{
    shape.move(xVelocity * dt.asSeconds(),
               yVelocity * dt.asSeconds());
}

// Set position (used to fix bat collision sticking)
void Ball::setPosition(Vector2f pos)
{
    shape.setPosition(pos);
}