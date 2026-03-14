#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace sf;

// Function prototype
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

int main() {
    srand(time(0));

    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber!", Style::Fullscreen);

    // Background
    Texture textureBackground;
    textureBackground.loadFromFile("background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    // Tree
    Texture textureTree;
    textureTree.loadFromFile("tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    // Branch Setup
    Texture textureBranch;
    textureBranch.loadFromFile("branch.png");
    for (int i = 0; i < NUM_BRANCHES; i++) {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        // Set origin to the center-left so rotation works correctly
        branches[i].setOrigin(220, 20);
    }

    // Player
    Texture texturePlayer;
    texturePlayer.loadFromFile("player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);
    side playerSide = side::LEFT;

    // RIP
    Texture textureRIP;
    textureRIP.loadFromFile("rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 2000);

    // Axe
    Texture textureAxe;
    textureAxe.loadFromFile("axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(2000, 830); // Hidden until chop

    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    // Flying Log
    Texture textureLog;
    textureLog.loadFromFile("log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    // Bee
    Texture textureBee;
    textureBee.loadFromFile("bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    float beeSpeed = 0.0f;
    bool beeActive = false;

    // Clouds
    Texture textureCloud;
    textureCloud.loadFromFile("cloud.png");
    Sprite clouds[3];
    bool cloudActive[3] = { false, false, false };
    float cloudSpeed[3] = { 0.0f, 0.0f, 0.0f };
    for (int i = 0; i < 3; i++) {
        clouds[i].setTexture(textureCloud);
    }

    // UI and Logic
    Clock clock;
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    timeBar.setSize(Vector2f(timeBarStartWidth, 80));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition(1920 / 2 - 200, 980);

    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
    int score = 0;
    bool paused = true;
    bool acceptInput = false;

    Font font;
    font.loadFromFile("KOMIKAP_.ttf");
    Text messageText, scoreText;
    messageText.setFont(font);
    scoreText.setFont(font);
    messageText.setString("Press Enter to Start");
    scoreText.setString("Score = 0");
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    messageText.setFillColor(Color::White);
    scoreText.setPosition(20, 20);

    // Center message text
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased && !paused) {
                acceptInput = true;
                spriteAxe.setPosition(2000, 830); // Hide axe on release
            }
            if (event.type == Event::Closed) window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();

        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;
            score = 0;
            timeRemaining = 6.0f;
            for (int i = 0; i < NUM_BRANCHES; i++) branchPositions[i] = side::NONE;
            spriteRIP.setPosition(600, 2000);
            spritePlayer.setPosition(580, 720);
            acceptInput = true;
            clock.restart();
        }

        if (!paused) {
            Time dt = clock.restart();
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, 80));

            if (timeRemaining <= 0.0f) {
                paused = true;
                messageText.setString("Out of time!!");
            }

            // Input handling
            if (acceptInput) {
                if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left)) {
                    bool right = Keyboard::isKeyPressed(Keyboard::Right);
                    playerSide = right ? side::RIGHT : side::LEFT;
                    score++;
                    timeRemaining += (2.0f / score) + 0.15f;

                    spriteAxe.setPosition(right ? AXE_POSITION_RIGHT : AXE_POSITION_LEFT, 830);
                    spritePlayer.setPosition(right ? 1200 : 580, 720);
                    
                    updateBranches(score);
                    spriteLog.setPosition(810, 720);
                    logSpeedX = right ? -5000 : 5000;
                    logActive = true;
                    acceptInput = false;

                    std::stringstream ss;
                    ss << "Score = " << score;
                    scoreText.setString(ss.str());
                }
            }

            // Move branches
            for (int i = 0; i < NUM_BRANCHES; i++) {
                float height = i * 150;
                if (branchPositions[i] == side::LEFT) {
                    branches[i].setPosition(610, height);
                    branches[i].setRotation(180);
                } else if (branchPositions[i] == side::RIGHT) {
                    branches[i].setPosition(1330, height);
                    branches[i].setRotation(0);
                } else {
                    branches[i].setPosition(3000, height);
                }
            }

            // Move Log
            if (logActive) {
                spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()), 
                                      spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));
                if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000) logActive = false;
            }

            // Death Check
            if (branchPositions[5] == playerSide) {
                paused = true;
                acceptInput = false;
                spriteRIP.setPosition(spritePlayer.getPosition().x, 760);
                spritePlayer.setPosition(2000, 2000);
                messageText.setString("SQUASHED!!");
            }

            // Bee and Clouds
            if (!beeActive) {
                beeSpeed = (rand() % 200) + 200;
                spriteBee.setPosition(2000, (rand() % 500) + 250);
                beeActive = true;
            } else {
                spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);
                if (spriteBee.getPosition().x < -100) beeActive = false;
            }

            for (int i = 0; i < 3; i++) {
                if (!cloudActive[i]) {
                    cloudSpeed[i] = (rand() % 200);
                    clouds[i].setPosition(-200, rand() % (150 * (i + 1)));
                    cloudActive[i] = true;
                } else {
                    clouds[i].setPosition(clouds[i].getPosition().x + (cloudSpeed[i] * dt.asSeconds()), clouds[i].getPosition().y);
                    if (clouds[i].getPosition().x > 1920) cloudActive[i] = false;
                }
            }
        }

        window.clear();
        window.draw(spriteBackground);
        for (int i = 0; i < 3; i++) window.draw(clouds[i]);
        for (int i = 0; i < NUM_BRANCHES; i++) window.draw(branches[i]);
        window.draw(spriteTree);
        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteLog);
        window.draw(spriteRIP);
        window.draw(spriteBee);
        window.draw(scoreText);
        window.draw(timeBar);
        if (paused) window.draw(messageText);
        window.display();
    }
    return 0;
}

void updateBranches(int seed) {
    for (int j = NUM_BRANCHES - 1; j > 0; j--) branchPositions[j] = branchPositions[j - 1];
    srand(seed + (int)time(0));
    int r = (rand() % 5);
    if (r == 0) branchPositions[0] = side::LEFT;
    else if (r == 1) branchPositions[0] = side::RIGHT;
    else branchPositions[0] = side::NONE;
}
