#include<SFML/Graphics.hpp>
#include<cmath>
#include<sstream>
#include<SFML/Audio.hpp>

using namespace sf;
using namespace std;


const int NUM_BRANCHES = 6;
 Sprite branches[NUM_BRANCHES];
enum class side{LEFT, RIGHT, NONE}; 
 side  branchPositions[NUM_BRANCHES];
void updateBranches(int seed);

int main(){
    VideoMode vm(1920,1080);
    RenderWindow window(vm, "Timber", Style::Fullscreen);
    
       // background
    Texture textureBackground;
    textureBackground.loadFromFile("background.png");
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0,0);
     
    //adding bee
    Texture textureBee;
    textureBee.loadFromFile("bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0,800);
    float beeSpeed =0.0f;
    bool beeActive = false;
        // ADD cloud
    Texture textureCloud;
    textureCloud.loadFromFile("cloud.png");
    Sprite spriteCloud1, spriteCloud2, spriteCloud3;
    spriteCloud1.setTexture(textureCloud);
     spriteCloud2.setTexture(textureCloud);
     spriteCloud3.setTexture(textureCloud);
     spriteCloud1.setPosition(0,100);
      spriteCloud2.setPosition(0,250);
       spriteCloud3.setPosition(0,500);
       
       bool cloud1Active = false;
       bool cloud2Active = false;
       bool cloud3Active = false;
       
       // cloud speed 
       float cloud1Speed = 0.0f;
       float cloud2Speed = 0.0f;
       float cloud3Speed = 0.0f;
     
     
    
        // adding tree
    Sprite spriteTree;
    Texture textureTree;
    textureTree.loadFromFile("tree.png");
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810,0);
    
    
    
     // time 
     Clock clock;
     bool paused = true;
     
     float timeRemaining = 6.0f;
     // adding timebar
     RectangleShape timeBar;
     float timeBarStartWidth = 400;
     float timeBarHeight = 80;
     timeBar.setSize(Vector2f( timeBarStartWidth, timeBarHeight));
     timeBar.setFillColor(Color::White);
     timeBar.setPosition((1920/2) -timeBarStartWidth /2, 890);
     float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
      
   
   
   
     
     // score
     int score = 0;
     Text messageText;
     Text scoreText;
     
     Font font;
     font.loadFromFile("KOMIKAP_.ttf");
     messageText.setFont(font);
     scoreText.setFont(font);
     messageText.setString("Press Enter to start");
     scoreText.setString("Score = 0");
     messageText.setCharacterSize(75);
     scoreText.setCharacterSize(100);
     messageText.setFillColor(Color::White);
     scoreText.setFillColor(Color::White);
     
     // positioning the text
     FloatRect textRect = messageText.getLocalBounds();
     messageText.setOrigin(textRect.left + textRect.width /2.0f, textRect.top+ textRect.height/2.0f);
     
     messageText.setPosition(1920/2.0f, 1080/2.0f);
     scoreText.setPosition(20,20); 
      
  // texture for 6 branches
  Texture textureBranch;
  textureBranch.loadFromFile("branch.png");
for(int i= 0; i<NUM_BRANCHES; i++){
    branches[i].setTexture(textureBranch);
    /* 
       branches[0] = texutreBranch;  -2000, -2000
        branches[1] = texutreBranch;  -2000, -2000
         branches[2] = texutreBranch;   -2000, -2000
          branches[3] = texutreBranch;  -2000, -2000
           branches[4] = texutreBranch;     -2000, -2000
    
    */
    
    
    branches[i].setPosition(-2000,-2000);
     branches[i].setOrigin(220,20);
     
    }
    // player
    Texture texturePlayer;
    texturePlayer.loadFromFile("player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580,720);
    side playerSide = side::LEFT;
    
    
    // rip 
    Texture textureRIP;
    textureRIP.loadFromFile("rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600,860);
    
    
    //axe 
    Texture textureAxe;
    textureAxe.loadFromFile("axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700,830);
    //  axe position
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;
    // log
    Texture textureLog;
    textureLog.loadFromFile("log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition( 810, 720);
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;
    
    bool acceptInput = false;
    
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);
    
    // crushed by branch
    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("death.wav");
    Sound death;
    death.setBuffer(deathBuffer);
    
    SoundBuffer ot;
    ot.loadFromFile("out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(ot);
    
    


   updateBranches(1);
     updateBranches(2);
     updateBranches(3);
     updateBranches(4);
     updateBranches(5);
    while(window.isOpen()){
     Event event;
       while(window.pollEvent(event)){
            if(event.type == Event:: KeyReleased && !paused){
                    acceptInput = true;
                    spriteAxe.setPosition(2000,spriteAxe.getPosition().y);
            }
            
            }
    // player input from keyboard
    if(Keyboard :: isKeyPressed(Keyboard:: Escape)){
        window.close();
    }
    
    // starting the game
    if(Keyboard :: isKeyPressed(Keyboard:: Return)){
          paused = false;
         
          // reset
          score = 0;
          timeRemaining = 6.0f;
          
          for(int i = 1; i<NUM_BRANCHES; i++){
               branchPositions[i] = side::NONE;
          }
          spriteRIP.setPosition(677, 2000);
          spritePlayer.setPosition(580,720);
          acceptInput = true;
    }
    
           
      //animation 
      if(acceptInput){
            if(Keyboard::isKeyPressed(Keyboard::Right)){
                 playerSide = side:: RIGHT;
                 score++;
                 timeRemaining += (2/score) + 0.15;
                  spriteAxe.setPosition(AXE_POSITION_RIGHT,spriteAxe.getPosition().y);
                  spritePlayer.setPosition(1200,720);
                  updateBranches(score);
                  spriteLog.setPosition(810,720);
                  logSpeedX = -5000;
                  logActive = true;
                  acceptInput = false;
                  chop.play();
                 
            }
         
          if(Keyboard::isKeyPressed(Keyboard::Left)){
                 playerSide = side:: LEFT;
                 score++;
                 timeRemaining += (2/score) + 0.15;
                  spriteAxe.setPosition(AXE_POSITION_LEFT,spriteAxe.getPosition().y);
                  spritePlayer.setPosition(580,720);
                  updateBranches(score);
                  spriteLog.setPosition(810,720);
                  logSpeedX = 5000;
                  logActive = true;
                  acceptInput = false;
                  chop.play();
                 
            }
      
      }
      
      
      if (!paused){
        Time dt = clock.restart();
        // adding timebar logic
           timeRemaining -=dt.asSeconds();
           timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));
           
           if( timeRemaining <= 0.0f){
                paused = true;
                messageText.setString("Out of time !!");
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width/2.0f , textRect.top+textRect.height / 2.0f);
                messageText.setPosition(1920/2.0f, 1080/2.0f); 
                outOfTime.play();
           }
        
      // bee movement
      if(!beeActive){
            srand((int) time (0));
            beeSpeed = (rand () % 200) + 200;
            //height of the bee
            srand((int)time(0) * 10);
            float height = (rand() %500 )+ 500;
            spriteBee.setPosition(2000,height);
            beeActive = true;
      }
      else{
            spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),spriteBee.getPosition().y);
            
            // if bee reached the left hand side of the screen
            if(spriteBee.getPosition().x <-100){
                beeActive = false;
            }
      }
      
      // cloud movements
      if (!cloud1Active){
           srand((int)time(0) * 10);
           cloud1Speed = (rand() %200);
           srand((int)time(0) * 10);
           float height = (rand()% 150);
           spriteCloud1 .setPosition(-200, height);
           cloud1Active = true;
      }
      else {
           spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);
           
           // if cloud reached right hand side of the screen 
           if(spriteCloud1.getPosition().x > 1920){
                cloud1Active = false;
           }        
      }
   //cloud 2
      if (!cloud2Active){
           srand((int)time(0) * 20);
           cloud2Speed = (rand() %200);
           srand((int)time(0) * 20);
           float height = (rand()% 300) -150 ;
           spriteCloud2 .setPosition(-200, height);
           cloud2Active = true;
      }
      else {
           spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);
           
           // if cloud reached right hand side of the screen 
           if(spriteCloud2.getPosition().x > 1920){
                cloud2Active = false;
           }        
      }
      
      // cloud3
          if (!cloud3Active){
           srand((int)time(0) * 30);
           cloud3Speed = (rand() %200);
           srand((int)time(0) * 30);
           float height = (rand()% 450) -150 ;
           spriteCloud3 .setPosition(-200, height);
           cloud3Active = true;
      }
      else {
           spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);
           
           // if cloud reached right hand side of the screen 
           if(spriteCloud3.getPosition().x > 1920){
                cloud3Active = false;
           }        
      }
     // score++;
      std::stringstream ss;
      ss<<"Score = "<<score;
      scoreText.setString(ss.str());
      
     for (int i= 0; i<NUM_BRANCHES; i++){
            float height = i * 150;
           if(branchPositions[i] == side::LEFT){
                        branches[i].setPosition(610,height); 
                        branches[i].setRotation(180);         
                       
              }
               else if(branchPositions[i] == side::RIGHT){
                       branches[i].setPosition(1330,height);   
                          branches[i].setRotation(0); 
               }
               else{
                          branches[i].setPosition(3000,height); 
               
               }
        }
        
         if(logActive){
                spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()) , spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));
                
                if(spriteLog.getPosition().x <-100 || spriteLog.getPosition().x > 2000){
                      logActive = false;
                      spriteLog.setPosition(810,720);
                
                }
                    
 
         }
         
         if(branchPositions[5] == playerSide){
             paused = true;
             acceptInput = false;
             spriteRIP.setPosition(525,760);
             spritePlayer.setPosition(2000,660);
             messageText.setString("Crushed By Branch !!");
             FloatRect textRect = messageText.getLocalBounds();
             messageText.setOrigin(textRect.left + textRect.width /2.0f, textRect.top + textRect.height / 2.0f);
             messageText.setPosition(1920/2.0f, 1080/2.0f);
             death.play();
             
         
         }
        
        //end of if paused
      }
   
       // Drawing
       window.clear();
       window.draw(spriteBackground);
       window.draw(spriteCloud1);
       window.draw(spriteCloud2);
       window.draw(spriteCloud3);
       for(int i=0 ; i<NUM_BRANCHES; i++){
                window.draw(branches[i]);
       }
       window.draw(spriteTree);
       window.draw(spritePlayer);
       window.draw(spriteAxe);
       window.draw(spriteLog);
       window.draw(spriteRIP);
       window.draw(spriteBee);
       window.draw(scoreText);
       window.draw(timeBar);
       if(paused){
            window.draw(messageText);
       
       }
       window.display();
    }
    
    
    return 0;
    
    }
    
    void updateBranches (int seed){
         for(int i =NUM_BRANCHES-1; i>0; i--){
               branchPositions[i] = branchPositions[i-1];;
         }
         
         srand((int)time(0)+ seed);
         int r = (rand() %5 );
         switch(r){
             case 0:
                     branchPositions[0] = side::LEFT;
                     break;
             case 1:
                         branchPositions[0] = side::RIGHT;
                           break;
                           
             default:
                           branchPositions[0] = side::NONE;
                           break;      
         }
    }
