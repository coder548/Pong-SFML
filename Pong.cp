#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif



using namespace sf;

int windowWidth = 1000;
int windowHeight = 700;
int batscore = 0;
int lives = -1;

int aibatcounter = 0;
class Bat {
private:
    Vector2f batPosition;
    double batSpeed = 0.85f;
    RectangleShape BatObject;

public:
    Bat(double x, double y);
    Vector2f getBatPosition();
    RectangleShape getBatObject();
    FloatRect getBatFloatRect();
    void moveBatLeft();
    void moveBatRight();
    void update();

};

class AIBat {
    private:
        Vector2f aiBatPosition;
        double aiBatSpeed = 24;
        RectangleShape aiBatObject;
        
    public:
        AIBat(double x, double y);
        Vector2f getAIBatPosition();
        RectangleShape getAIBatObject();
        FloatRect getAIBatFloatRect();
    void moveAIBatLeft();
        void moveAIBatRight();
        void update();
    void Rebound();
    void AIBatSpeedReverse();

    };


class Ball {
    private:
    
    RectangleShape BallObject;
    Vector2f ballPosition;
    public:
    RectangleShape getBallObject();
    Ball(double x, double y);
    FloatRect getBallFloatRect();
    void reboundSides();
    void passTop();
    Vector2f getBallPosition;
    void passBottom();
    void intersectBat();
    void intersectAIBat();
    void reboundBatorAI();
    void update();
    double ballVelocityX = 0.5f;
    double ballVelocityY = 0.5f;
    void stop();
    void go();
        
};

//INT MAIN/////////////////

int main () {
    
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");


    
    
    // creating objects
           Bat bat(windowWidth/2, windowHeight-20);
           Ball ball(windowWidth/2+50, windowHeight/2);
           AIBat aibat(windowWidth/2, 10);
    
    while (window.isOpen()) {
    
    Event event;
    while (window.pollEvent(event)) {
        if(event.type==Event::Closed)
            window.close();
    }
    
       
        
        //USER INPUT
        
        if(((event.type == event.KeyPressed) && event.key.code == Keyboard::Left)) {
            bat.moveBatLeft();
        }
        
    if(((event.type == event.KeyPressed) && event.key.code == Keyboard::Right)) {
    
        bat.moveBatRight();
        }
        
        //LOGIC//////////
        ball.reboundSides();
        ball.passTop();
        ball.passBottom();
        
        if (ball.getBallFloatRect().intersects(bat.getBatFloatRect())) {
     ball.reboundBatorAI();
                        
        }
        
        if (ball.getBallFloatRect().intersects(aibat.getAIBatFloatRect())) {
        
ball.reboundBatorAI();
                           
           }

        if (ball.getBallFloatRect().left > (aibat.getAIBatFloatRect().left) + 50) {
              if (aibatcounter % 60 == 0) aibat.moveAIBatRight();
        }
        
        if (ball.getBallFloatRect().left < (aibat.getAIBatFloatRect().left) + 50) {
              if (aibatcounter % 60 == 0) aibat.moveAIBatLeft();
        }
    


        if (ball.getBallPosition.x > windowWidth)
            aibat.AIBatSpeedReverse();
      
        
        //TEXT and FONT
        std::stringstream ss;
                
        ss << "Score: " << batscore <<"       Lives: " << lives;
         
        Text text;
        Font font;
        font.loadFromFile("Nexa Light.otf");

        text.setFont(font);
        text.setCharacterSize(45);
        text.setFillColor(sf::Color::White);
        
        text.setString(ss.str());

        
        // PAUSE MESSAGE
        
        std::stringstream ss2;
        ss2 << "You ran out of lives. \n\nYour score is " << batscore <<".\n\nPress any key to play again.";
         Text pauseMessage;
        
        
        pauseMessage.setCharacterSize(50);
         pauseMessage.setPosition(windowWidth/2-400, windowHeight/2-100);
        pauseMessage.setFont(font);
    pauseMessage.setString(ss2.str());
        // START MESSAGE
            std::stringstream ss3;
            ss3 << "Welcome to Pong.\n\nPress any key to begin";
             Text startMessage;
            
            startMessage.setCharacterSize(50);
             startMessage.setPosition(windowWidth/2-400, windowHeight/2-100);
            startMessage.setFont(font);
        startMessage.setString(ss3.str());
        // UPDATE
        if(aibatcounter == 1000000) {
            aibatcounter = 0;
        }
        aibatcounter++;
        ball.update();
        bat.update();
    aibat.update();
        // DRAW
        window.clear(Color(26, 128, 182, 255));
       
        if (lives == 0) {
            
    window.draw(pauseMessage);
            ball.stop();
            
        if(event.type == event.KeyPressed) {
            lives = 3;
            batscore = 0;
            ball.go();
                 }
        }
        else if (lives == -1) {
            window.draw(startMessage);
            ball.stop();
            if(event.type == event.KeyPressed) {
                     lives = 3;
                     batscore = 0;
                     ball.go();
                          }
                 }

        
        else {
    window.draw(bat.getBatObject());
        window.draw(ball.getBallObject());
            
            window.draw(text);
                window.draw((aibat.getAIBatObject()));
        }
        window.display();
    }
    
    return 0;
}

// BAT functions

Bat::Bat (double x, double y) {
    batPosition.x = x;
    batPosition.y = y;
    BatObject.setSize(sf::Vector2f(150, 10));
    BatObject.setPosition(batPosition);

}

Vector2f Bat::getBatPosition() {
    return batPosition;
}

RectangleShape Bat::getBatObject() {
    return BatObject;
}

FloatRect Bat::getBatFloatRect() {
    return BatObject.getGlobalBounds();
}
void Bat::moveBatLeft() {
    batPosition.x -= batSpeed;
}
void Bat::moveBatRight() {
    batPosition.x += batSpeed;
}
void Bat::update() {
    BatObject.setPosition(batPosition);
}

// AIBAT functions
AIBat::AIBat (double x, double y) {
    aiBatPosition.x = x;
    aiBatPosition.y = y;
    aiBatObject.setSize(sf::Vector2f(150, 10));
    aiBatObject.setPosition(aiBatPosition);

}

RectangleShape AIBat::getAIBatObject() {
    return aiBatObject;
}

Vector2f AIBat::getAIBatPosition() {
    return aiBatPosition;
}

FloatRect AIBat::getAIBatFloatRect() {
    return aiBatObject.getGlobalBounds();
}

void AIBat::moveAIBatLeft() {
        aiBatPosition.x -= aiBatSpeed;
}
void AIBat::moveAIBatRight() {
aiBatPosition.x += aiBatSpeed;
}

void AIBat::update() {
    aiBatObject.setPosition(aiBatPosition);
    
}

void AIBat::AIBatSpeedReverse () {
    aiBatSpeed *= -1;
}

// BALL functions
RectangleShape Ball::getBallObject() {
    return BallObject;
}

Ball::Ball(double x, double y) {
    ballPosition.x = x;
    ballPosition.y = y;
    BallObject.setSize(sf::Vector2f(10, 10));
    
    BallObject.setPosition(ballPosition);
    
    BallObject.setFillColor(sf::Color::White);
    
}

void Ball::update() {
   
    
    ballPosition.x += ballVelocityX;
    ballPosition.y += ballVelocityY;
    
    
BallObject.setPosition(ballPosition);
}


void Ball::reboundSides() {
    if (ballPosition.x > windowWidth)
        ballVelocityX *=  -1;
        
        else if (ballPosition.x <0)
            ballVelocityX *= -1;
    
    
        }


    void Ball::passTop() {

            if (ballPosition.y < 0)
            {
                batscore++;
                ballPosition.x = windowWidth /2 ;
                ballPosition.y = windowHeight / 2;

                if(rand() % 2 == 1) ballVelocityY *= -1;
                if (rand()% 2 == 2) ballVelocityX *= -1;
                
    }
    }
void Ball::passBottom()  {
  if (ballPosition.y > windowHeight+10)
  { ballPosition.x = windowWidth/2;
      ballPosition.y = windowHeight/2;
      lives--;
       if(rand() % 2 == 1) ballVelocityY *= -1;
        if (rand()% 2 == 2) ballVelocityX *= -1;
  }
    

}
FloatRect Ball::getBallFloatRect() {return BallObject.getGlobalBounds();}
    

void Ball::reboundBatorAI() {
    ballPosition.y -= (ballVelocityY * 30);
    ballVelocityY *= -1;
    
}

void Ball::stop () {
    ballVelocityY = 0;
    ballVelocityX = 0;
}

void Ball::go () {
    ballVelocityY = 0.5f;
    ballVelocityX = 0.5f;
}
