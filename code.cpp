#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace sf;

int main() {
    // 1. Setup the Window
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber", Style::Fullscreen);

    // 2. Load Textures and Sprites
    Texture textureBackground;
    textureBackground.loadFromFile("background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    Texture textureTree;
    textureTree.loadFromFile("tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    // Bee Setup
    Texture textureBee;
    textureBee.loadFromFile("bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    
    bool beeActive = false;
    float beeSpeed = 0.0f;
    float beeBaseHeight = 0.0f; // Central height for the sine wave

    // Clouds Setup
    Texture textureCloud;
    textureCloud.loadFromFile("cloud.png");
    Sprite spriteCloud1, spriteCloud2, spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    bool cloud1Active = false, cloud2Active = false, cloud3Active = false;
    float cloud1Speed = 0.0f, cloud2Speed = 0.0f, cloud3Speed = 0.0f;

    // Time Control
    Clock clock;
    float totalTime = 0.0f; // Used for the sine wave calculation

    // 3. Main Game Loop
    while (window.isOpen()) {
        
        // --- Handle Input & Window Events ---
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }

        // --- Update the Scene ---
        Time dt = clock.restart();
        totalTime += dt.asSeconds();

        // Bee Sine Wave Movement
        if (!beeActive) {
            srand((int)time(0));
            beeSpeed = (rand() % 200) + 200;
            beeBaseHeight = (rand() % 500) + 200; 
            spriteBee.setPosition(2000, beeBaseHeight);
            beeActive = true;
        } else {
            float newX = spriteBee.getPosition().x - (beeSpeed * dt.asSeconds());
            
            // Formula: BaseHeight + (Amplitude * sin(Frequency * TotalTime))
            float newY = beeBaseHeight + (150.0f * sin(totalTime * 4.0f));
            
            spriteBee.setPosition(newX, newY);

            if (spriteBee.getPosition().x < -100) {
                beeActive = false;
            }
        }

        // Cloud 1 Logic
        if (!cloud1Active) {
            srand((int)time(0) * 10);
            cloud1Speed = (rand() % 200);
            spriteCloud1.setPosition(-400, (rand() % 150));
            cloud1Active = true;
        } else {
            spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);
            if (spriteCloud1.getPosition().x > 1920) cloud1Active = false;
        }

        // Cloud 2 Logic
        if (!cloud2Active) {
            srand((int)time(0) * 20);
            cloud2Speed = (rand() % 200);
            spriteCloud2.setPosition(-400, (rand() % 300) + 150);
            cloud2Active = true;
        } else {
            spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);
            if (spriteCloud2.getPosition().x > 1920) cloud2Active = false;
        }

        // Cloud 3 Logic
        if (!cloud3Active) {
            srand((int)time(0) * 30);
            cloud3Speed = (rand() % 200);
            spriteCloud3.setPosition(-400, (rand() % 450) + 300);
            cloud3Active = true;
        } else {
            spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);
            if (spriteCloud3.getPosition().x > 1920) cloud3Active = false;
        }

        //Draw the Scene
        window.clear();
        window.draw(spriteBackground);
        
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);
        
        window.draw(spriteTree);
        window.draw(spriteBee);
        
        window.display();
    }

    return 0;
}
