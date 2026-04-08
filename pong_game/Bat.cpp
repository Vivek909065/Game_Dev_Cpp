#include "Bat.h"

Bat::Bat(float startX, float startY)
{
    shape.setSize(Vector2f(150, 20));
    shape.setFillColor(Color::White);
    shape.setPosition(startX, startY);
}

FloatRect Bat::getPosition()
{
    return shape.getGlobalBounds();
}

RectangleShape Bat::getShape()
{
    return shape;
}

void Bat::moveLeft()
{
    movement = -speed;
}

void Bat::moveRight()
{
    movement = speed;
}

void Bat::stop()
{
    movement = 0;
}

void Bat::update(Time dt)
{
    shape.move(movement * dt.asSeconds(), 0);
}