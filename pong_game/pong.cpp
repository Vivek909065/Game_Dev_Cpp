#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Pong", Style::Fullscreen);

    int score = 0;
    int lives = 3;
    bool isGameOver = false;
    bool ballHitBat = false; // collision flag

    Bat bat(1920 / 2, 1080 - 50);
    Ball ball(1920 / 2, 0);

    Font font;
    font.loadFromFile("font/DS-DIGI.TTF");

    Text hud;
    hud.setFont(font);
    hud.setCharacterSize(60);
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(120);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setString("GAME OVER\nPress Enter");
    gameOverText.setPosition(500, 400);

    Clock clock;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
            window.close();

        // Restart game
        if (isGameOver && Keyboard::isKeyPressed(Keyboard::Enter))
        {
            score = 0;
            lives = 3;
            isGameOver = false;
            ballHitBat = false;
            ball = Ball(1920 / 2, 0);
        }

        // Input
        if (!isGameOver)
        {
            if (Keyboard::isKeyPressed(Keyboard::Left))
                bat.moveLeft();
            else if (Keyboard::isKeyPressed(Keyboard::Right))
                bat.moveRight();
            else
                bat.stop();
        }

        Time dt = clock.restart();

        if (!isGameOver)
        {
            bat.update(dt);
            ball.update(dt);
        }

        // HUD
        std::stringstream ss;
        ss << "Score: " << score << "    Lives: " << lives;
        hud.setString(ss.str());

        if (!isGameOver)
        {
            // Ball falls below window
            if (ball.getPosition().top > window.getSize().y)
            {
                ball.reboundBottom();
                lives--;

                if (lives <= 0)
                {
                    isGameOver = true;
                }
            }

            // Ball hits top
            if (ball.getPosition().top < 0)
            {
                ball.reboundBatOrTop();
                score++;
            }

            // Ball hits sides
            if (ball.getPosition().left < 0 ||
                ball.getPosition().left + ball.getSize() > window.getSize().x)
            {
                ball.reboundSides();
            }

            // Bat collision (fixed)
            if (ball.getPosition().intersects(bat.getPosition()))
            {
                if (!ballHitBat)
                {
                    ball.reboundBatOrTop();

                    // Move ball above bat to prevent sticking
                    FloatRect batPos = bat.getPosition();
                    ball.setPosition(Vector2f(
                        ball.getPosition().left,
                        batPos.top - ball.getSize() - 1
                    ));

                    score++;
                    ballHitBat = true;
                }
            }
            else
            {
                ballHitBat = false;
            }
        }

        window.clear();

        if (isGameOver)
        {
            window.draw(gameOverText);
        }
        else
        {
            window.draw(hud);
            window.draw(bat.getShape());
            window.draw(ball.getShape());
        }

        window.display();
    }

    return 0;
}