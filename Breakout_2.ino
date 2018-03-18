// Christian Orrico
// January 28th, 2018
// breakout with a twist

#include <Arduboy2.h>                                                            // include the arduboy and tones libraries                                                  
#include <ArduboyTones.h>
Arduboy2 arduboy;
ArduboyTones sound(arduboy.audio.enabled);

// Variables declared here
int troll = 0;
int gamestate = 0;
int justpressed = 0;
int ballx = 54;
int bally = 32;
int ballsize = 2;
int ballright = 1;
int balldown = -1;
int paddlewidth = 9;
int paddleheight = 2;
int rectanglewidth = 7;
int rectangleheight = 2;
int playerx = 58;
int playery = 58;
int level = 1;
int actualLevel = 1;
int lives = 3;
int loopCount = 0;
int blocksHit = 0;
int blocksInLevel = 16;
int hitRectangles[48] = {};
int rectCordsx[48] = {};
int rectCordsy[48] = {};
int ballSpeed = 15;
int played = 0;
const uint16_t song_of_storms[] PROGMEM = {                                         // background music song
  NOTE_D4,150, NOTE_F4,150, NOTE_D5,600,
  NOTE_D4,150, NOTE_F4,150, NOTE_D5,600,
  NOTE_E5,450, NOTE_F5,150, NOTE_E5,150,
  NOTE_F5,150, NOTE_E5,150, NOTE_C5,150,
  NOTE_A4,600, NOTE_A4,300, NOTE_D4,300,
  NOTE_F4,150, NOTE_G4,150, NOTE_A4,900,
  NOTE_A4,300, NOTE_D4,300, NOTE_F4,150,
  NOTE_G4,150, NOTE_E4,900, NOTE_D4,150, 
  NOTE_F4,150, NOTE_D5,600, NOTE_D4,150,
  NOTE_F4,150, NOTE_D5,600, NOTE_E5,450,
  NOTE_F5,150, NOTE_E5,150, NOTE_F5,150,
  NOTE_E5,150, NOTE_C5,150, NOTE_A4,600,
  NOTE_A4,300, NOTE_D4,300, NOTE_F4,150,
  NOTE_G4,150, NOTE_A4,600, NOTE_A4,300,
  NOTE_D4,1500, NOTE_REST,300,
  TONES_REPEAT
};
const uint16_t easter_egg[] PROGMEM = {                                                                                // easter egg song that plays when you beat level 7
  NOTE_A4,300, NOTE_E5,150, NOTE_E5,150, NOTE_E5,900, NOTE_E5,150, NOTE_C5,150, NOTE_D5,300, NOTE_B4,300, NOTE_A4,1800, 
  NOTE_E4,300, NOTE_E4,300, NOTE_A4,300, NOTE_E5,150, NOTE_E5,150, NOTE_E5,900, NOTE_E5,150, NOTE_C5,150, NOTE_D5,300, 
  NOTE_B4,300, NOTE_A4,2100, NOTE_E4,300, NOTE_A4,300, NOTE_C5,300, NOTE_B4,300, NOTE_G4,300, NOTE_E4,900, NOTE_E4,300,
  NOTE_A4,300, NOTE_C5,300, NOTE_B4,300, NOTE_G4,300, NOTE_E5,900, NOTE_E4,300, NOTE_A4,300, NOTE_C5,300, NOTE_B4,300, 
  NOTE_G4,300, NOTE_E4,900, NOTE_D4,300, NOTE_E4,1200, NOTE_REST,1200,

  NOTE_A4,600, NOTE_C5,600, NOTE_B4,900, NOTE_G4,300, NOTE_A4,300, NOTE_C5,300, NOTE_B4,300, NOTE_A4,300, NOTE_G4,600,
  NOTE_E4,600, NOTE_A4,600, NOTE_C5,600, NOTE_B4,900, NOTE_G4,300, NOTE_A4,300, NOTE_C5,300, NOTE_B4,300, NOTE_G4,300,
  NOTE_A4,1200, NOTE_A4,600, NOTE_C5,600, NOTE_B4,900, NOTE_G4,300, NOTE_A4,300, NOTE_C5,300, NOTE_B4,300, NOTE_A4,300, 
  NOTE_G4,600, NOTE_E4,600, NOTE_A4,600, NOTE_C5,600, NOTE_B4,900, NOTE_G4,300, NOTE_A4,300, NOTE_C5,300, NOTE_B4,300, 
  NOTE_G4,300, NOTE_A4,1200, NOTE_E5,600, NOTE_E5,600, NOTE_D5,900, NOTE_B4,300, NOTE_E5,600, NOTE_D5,300, NOTE_C5,300,
  NOTE_B4,1200, NOTE_E5,600, NOTE_E5,600, NOTE_D5,900, NOTE_C5,300, NOTE_B4,600, NOTE_B4,600, NOTE_A4,1200, NOTE_E5,600, 
  NOTE_E5,600, NOTE_D5,1200, NOTE_E5,600, NOTE_D5,300, NOTE_C5,300, NOTE_B4,1200, NOTE_E5,300, NOTE_F5,300, NOTE_E5,300,
  NOTE_D5,300, NOTE_C5,600, NOTE_B4,600, NOTE_A4,1200, NOTE_REST,1200,

  NOTE_E4,300, NOTE_B4,150, NOTE_C5,150, NOTE_B4,300, NOTE_A4,300, NOTE_G4,150, NOTE_A4,150, NOTE_G4,150, NOTE_FS4,150,
  NOTE_E4,300, NOTE_E4,300, NOTE_E4,300, NOTE_G4,150, NOTE_A4,150, NOTE_G4,300, NOTE_FS4,300, NOTE_E4,150, NOTE_FS4,150,
  NOTE_E4,150, NOTE_D4,150, NOTE_E4,300, NOTE_REST,300, NOTE_E4,300, NOTE_B4,150, NOTE_C5,150, NOTE_B4,300, NOTE_A4,300, 
  NOTE_G4,150, NOTE_A4,150, NOTE_G4,150, NOTE_FS4,150, NOTE_E4,300, NOTE_E4,300, NOTE_E4,150, NOTE_FS4,150, NOTE_G4,150,
  NOTE_A4,150, NOTE_G4,300, NOTE_FS4,300, NOTE_E4,300, NOTE_D4,300, NOTE_E4,300, NOTE_REST,300, NOTE_D5,300, NOTE_A4,300,
  NOTE_A4,150, NOTE_B4,150, NOTE_C5,150, NOTE_D5,150, NOTE_C5,300, NOTE_B4,300, NOTE_B4,300, NOTE_G4,300, NOTE_D5,300, 
  NOTE_A4,300, NOTE_A4,150, NOTE_B4,150, NOTE_C5,150, NOTE_D5,150, NOTE_B4,1200, NOTE_D5,300, NOTE_A4,300, NOTE_A4,150,
  NOTE_B4,150, NOTE_C5,150, NOTE_D5,150, NOTE_B4,300, NOTE_G4,300, NOTE_G4,300, NOTE_B4,300, NOTE_A4,300, NOTE_G4,150,
  NOTE_FS4,150, NOTE_E4,300, NOTE_D4,300, NOTE_E4,900, NOTE_REST,1500,

  NOTE_D4,900, NOTE_E4,150, NOTE_F4,150, NOTE_G4,600, NOTE_C5,300, NOTE_D5,600, NOTE_G4,300, NOTE_E4,600, NOTE_D4,900,
  NOTE_G4,300, NOTE_E4,600, NOTE_D4,150, NOTE_C4,150, NOTE_D4,600, NOTE_G4,300, NOTE_E4,600, NOTE_D5,900, NOTE_E5,150,
  NOTE_F5,150, NOTE_G5,600, NOTE_C6,300, NOTE_D6,600, NOTE_G5,300, NOTE_E5,600, NOTE_D5,900, NOTE_G5,300, NOTE_E5,600, 
  NOTE_D5,150, NOTE_C5,150, NOTE_D5,600, NOTE_G5,300, NOTE_E5,600, NOTE_A4,900, NOTE_A4,150, NOTE_G4,150, NOTE_F4,600,
  NOTE_F4,300, NOTE_E4,450, NOTE_D4,150, NOTE_G4,600, NOTE_E4,300, NOTE_C4,600, NOTE_D4,300, NOTE_D4,300, NOTE_E4,300,
  NOTE_B3,300, NOTE_A3,1800, NOTE_A5,900, NOTE_A5,150, NOTE_G5,150, NOTE_F5,600, NOTE_F5,300, NOTE_E5,450, NOTE_D5,150, 
  NOTE_G5,600, NOTE_E5,300, NOTE_C5,600, NOTE_D5,300, NOTE_D5,300, NOTE_E5,300, NOTE_B4,300, NOTE_A4,1800, NOTE_D4,900, 
  NOTE_E4,150, NOTE_F4,150, NOTE_G4,600, NOTE_C5,300, NOTE_D5,600, NOTE_G4,300, NOTE_E4,600, NOTE_D4,900, NOTE_G4,300,
  NOTE_E4,600, NOTE_D4,900, NOTE_REST,900,

  NOTE_REST,150, NOTE_CS4,150, NOTE_FS4,150, NOTE_GS4,150, NOTE_A4,450, NOTE_CS4,150, NOTE_FS4,150, NOTE_GS4,150, NOTE_A4,750,
  NOTE_D4,150, NOTE_FS4,150, NOTE_GS4,150, NOTE_A4,450, NOTE_D4,150, NOTE_FS4,150, NOTE_GS4,150, NOTE_A4,750, NOTE_B3,150,
  NOTE_E4,150, NOTE_FS4,150, NOTE_GS4,450, NOTE_B3,150, NOTE_E4,150, NOTE_FS4,150, NOTE_GS4,750, NOTE_FS4,150, NOTE_GS4,150,
  NOTE_FS4,150, NOTE_F4,600, NOTE_REST,1200, NOTE_REST,150, NOTE_CS4,150, NOTE_FS4,150, NOTE_GS4,150, NOTE_A4,450, NOTE_CS4,150, 
  NOTE_FS4,150, NOTE_GS4,150, NOTE_A4,750, NOTE_D4,150, NOTE_FS4,150, NOTE_GS4,150, NOTE_A4,450, NOTE_D4,150, NOTE_FS4,150,
  NOTE_GS4,150, NOTE_A4,750, NOTE_B3,150, NOTE_E4,150, NOTE_FS4,150, NOTE_GS4,450, NOTE_B3,150, NOTE_E4,150, NOTE_FS4,150, 
  NOTE_GS4,750, NOTE_FS4,150, NOTE_GS4,150, NOTE_FS4,150, NOTE_F4,600, NOTE_REST,1500, NOTE_D4,500, NOTE_D5,450, NOTE_CS5,450,
  NOTE_B4,450, NOTE_GS4,300, NOTE_A4,600, NOTE_A4,150, NOTE_B4,150, NOTE_A4,150, NOTE_GS4,1350, NOTE_REST,300, NOTE_D4,500,
  NOTE_CS5,450, NOTE_B4,450, NOTE_A4,450, NOTE_FS4,300, NOTE_E4,600, NOTE_FS4,150, NOTE_GS4,150, NOTE_FS4,150, NOTE_F4,1350,
  NOTE_REST,300, NOTE_D4,500, NOTE_D5,450, NOTE_CS5,450, NOTE_B4,450, NOTE_GS4,300, NOTE_A4,600, NOTE_A4,150, NOTE_B4,150, NOTE_A4,150, 
  NOTE_GS4,900, NOTE_D4,300, NOTE_E4,900, NOTE_A4,300, NOTE_GS4,900, NOTE_E4,300, NOTE_FS4,1200, NOTE_REST,1200,

  TONES_REPEAT  
}; 
void resetgame() {                                                                        // function to reset the game if you lose
  ballx = 58;
  bally = 32;
  playerx = 58;
  ballright = 1;
  balldown = -1;
  level = 1;
  actualLevel = 1;
  lives = 3;
  for(int i = 0; i < 48; i++) {                                                           // delete all values in the lists
    hitRectangles[i] = 0;
    rectCordsx[i] = '\O';
    rectCordsy[i] = '\O';
  }
}
void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  sound.volumeMode(VOLUME_ALWAYS_HIGH);                                                   // make the volume loud
  arduboy.audio.on();                                                                     // turn on the volume
  // Set the game to 60 frames per second
  arduboy.setFrameRate(60);
  for(int i = 0; i < 48; i++) {
    rectCordsx[i] = '\O';
    rectCordsy[i] = '\O'; 
}
  arduboy.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Prevent the Arduboy from running too fast
  if(!arduboy.nextFrame()) {
    return;
  }
  arduboy.clear();

  switch(gamestate) {
    case 0:
          arduboy.setCursor(6, 27);
          arduboy.setTextSize(2);
          arduboy.print("Breakout 2");
          arduboy.setTextSize(1);
          // Change the gamestate
          if(arduboy.pressed(A_BUTTON) and justpressed == 0) {
            justpressed = 1;
            gamestate = 1;
          }
          break;
    case 1:
          // Gameplay screen
          if(level > 3 and level < 7) {                                               // after level 3, the ball will move twice as fast. the ball is partially slowed down by a delay
            delay(ballSpeed);
          }
          arduboy.audio.on();                                                         // turn on the music
          if(played == 0) {                                                           // only start playing the background music once
            sound.tones(song_of_storms);                                              // play the background music
            played = 1;
          }
          arduboy.setCursor(10, 0);                                                   // display the level and the amount of lives left
          arduboy.print("level ");
          arduboy.print(actualLevel);
          arduboy.setCursor(75, 0);
          arduboy.print(lives);
          arduboy.print(" lives");
          arduboy.fillRect(ballx, bally, ballsize, ballsize, WHITE);                  // draw the ball
          for(int yCord = 10; yCord <= 16; yCord+=3) {                                // for loops to draw a brick on each x and y location
            for(int xCord = 0; xCord <= 127; xCord+=8) {
            if(hitRectangles[loopCount] != 1) {                                       // only draw the brick if the brick has not been hit
              arduboy.fillRect(xCord, yCord, rectanglewidth, rectangleheight, WHITE); // draw the brick
              rectCordsx[loopCount] = xCord;                                          // assign values to the list of x and y coordinates          
              rectCordsy[loopCount] = yCord;
            }
            loopCount = loopCount + 1;                                                // count the number of times the computer went through the loop  
          }
          if(level == 1 or level == 4 or level == 7) {                                // draw only one row in levels 1, 4, and 7
            break; 
          }    
          if((level == 2 or level == 5) and yCord == 13) {                            // in level 2 and 5, draw two rows. if the rest of the levels, draw three rows
            break;    
          }
          }
          loopCount = 0;                                                              // reset the loop count
          for(int i = 0; i < 48; i++) {                                               // check every brick for collision
            if(level > 3) {                                                           // if the level is greater than three, the ball will go twice as fast, so it needs to check one pixel after the brick as well as the brick
              if((bally == rectCordsy[i] + rectangleheight or bally - 1 == rectCordsy[i] + rectangleheight) and ballx <= rectCordsx[i] + rectanglewidth and ballx + paddlewidth >= rectCordsx[i]) {          // check collision from below 
              balldown = 1;                                                                             // reverse the direction
              hitRectangles[i] = 1;                                                                     // assign the brick to hit
              arduboy.fillRect(rectCordsx[i], rectCordsy[i], rectanglewidth, rectangleheight, BLACK);   // delete the brick by drawing black over it
              rectCordsx[i] = '\O';                                                                     // delete the coordinates of the box
              rectCordsy[i] = '\O';
            }
              else if((bally + ballsize == rectCordsy[i] or bally + 1 == rectCordsy[i]) and ballx <= rectCordsx[i] + rectanglewidth and ballx + paddlewidth >= rectCordsx[i]) {                              // check collision from above
              balldown = -1; 
              hitRectangles[i] = 1;
              arduboy.fillRect(rectCordsx[i], rectCordsy[i], rectanglewidth, rectangleheight, BLACK);
              rectCordsx[i] = '\O';
              rectCordsy[i] = '\O';
              }
            }  
            // collision checking for levels below three
            else if(bally == rectCordsy[i] + rectangleheight and ballx <= rectCordsx[i] + rectanglewidth and ballx + paddlewidth >= rectCordsx[i]) {
              balldown = 1;
              hitRectangles[i] = 1;
              arduboy.fillRect(rectCordsx[i], rectCordsy[i], rectanglewidth, rectangleheight, BLACK);
              rectCordsx[i] = '\O';
              rectCordsy[i] = '\O';
            }  
            else if(bally + ballsize == rectCordsy[i] and ballx <= rectCordsx[i] + rectanglewidth and ballx + paddlewidth >= rectCordsx[i]) {
              balldown = -1;
              hitRectangles[i] = 1;
              arduboy.fillRect(rectCordsx[i], rectCordsy[i], rectanglewidth, rectangleheight, BLACK);
              rectCordsx[i] = '\O';
              rectCordsy[i] = '\O';
            }
          }
                   
          // Move the ball right
          if(ballright == 1) {
            if(level > 3) {                                           // the ball moves twice as fast after level three
             ballx = ballx + 2;
            }
            else {
              ballx = ballx + 1;
            }   
          }
          // Move the ball left
          if(ballright == -1) {
            if(level > 3) {
             ballx = ballx - 2;
            }
            else {
              ballx = ballx - 1;
            }
          }
          // Move the ball down
          if(balldown == 1) {
            if(level > 3) {
              bally = bally + 2;
            }
            else {
              bally = bally + 1;
            }
          }
          // Move the ball up
          if(balldown == -1) {
            if(level > 3) {
              bally = bally - 2;
            }
            else {
              bally = bally - 1;
            }
          }
          // Reflect the ball off of the top of the screen
          if(bally <= 0) {
            balldown = 1;
          }
          // Reflect the ball off the left of the screen
          if(ballx <= 0) {
            ballright = 1;
          }
          // Reflect the ball off the right of the screen
          if(ballx + ballsize >= 127) {
            ballright = -1; 
          }
          // Draw the player's paddle
          arduboy.fillRect(playerx, playery, paddlewidth, paddleheight, WHITE);
          // If the player pressed up and the paddle is not touching the top
          if(arduboy.pressed(LEFT_BUTTON) and playerx > 0) {
            if(level > 3) {
              playerx = playerx - 2;
            }
            else {
              playerx = playerx - 1;
            }
          }
          // If the player pressed down and the paddle is not touching the bottom
          if(arduboy.pressed(RIGHT_BUTTON) and playerx + paddlewidth < 127) {
            if(level > 3) {
              playerx = playerx + 2;
            }
            else {
              playerx = playerx + 1;
            }  
          }
          // If the ball moves below the screen...
          if(bally > 63) {
            // Move the ball back to the middle of the screen
            ballx = 58;
            bally = 32;
            if(playerx >= 58) {
              ballright = 1;
            }
            else {
              ballright = -1;
            }
            balldown = -1;
            lives = lives - 1;
          }
          // Check if you lose
          if(lives == 0) {
            gamestate = 3;
          }
          if(level == 1 or level == 4 or level == 7) {                                         // assign a value to the number of blocks in the level
            blocksInLevel = 16;
          }
          if(level == 2 or level == 5) {
            blocksInLevel = 32;
          }
          if(level == 3 or level == 6) {
            blocksInLevel = 48;
          }
          // check the number of blocks hit
          for(int i = 0; i < 48; i++) { 
            if(hitRectangles[i] == 1) {
              blocksHit = blocksHit + 1;
            }
          }
          // if all blocks are hit, you beat the level
          if(blocksHit == blocksInLevel) {   
            level = level + 1;                                                                 // go to next level
            actualLevel = actualLevel + 1;
            for(int i = 0; i < 48; i++) {                                                      // all hit rectangles are no longer hit
              hitRectangles[i] = 0;
            }
            ballx = 58;                                                                        // reset the ball and ball direction
            bally = 32;
            playerx = 58;
            balldown = -1;
            ballright = 1;
            if(level < 8) {                                                                    // go to the completed level screen if you beat a regular level
            gamestate = 2;
          }
            else if(level > 7) {                                                                  // if you beat level 7, go to special win screen                                                          //
            gamestate = 4;
          }
          }
          blocksHit = 0;
          // If the ball makes contact with the player's paddle, bounce it off
          if(bally + ballsize == playery and playerx <= ballx + ballsize and playerx + paddlewidth >= ballx) {
            balldown = -1;
          }
          break;
    case 2:
          // Win screen
          arduboy.setCursor(20, 31);
          arduboy.print("Level completed!");
          // Change the gamestate
          if(arduboy.pressed(A_BUTTON) and justpressed == 0) {
            justpressed = 1;
            gamestate = 1;
          }
          break;
    case 3:
          // Game over screen
          arduboy.audio.off();
          played = 0;
          arduboy.setCursor(40, 31);
          arduboy.print("Game Over");
          // Change the gamestate
          if(arduboy.pressed(A_BUTTON) and justpressed == 0) {
            justpressed = 1;
            resetgame();
            gamestate = 0;
          }
          break;
     case 4:
          // you beat the game
          arduboy.setCursor(40, 31);
          arduboy.print("YOU WIN!!");
          if(played == 1) {
            sound.tones(easter_egg);                                              // play easter egg song
            played = 0;
          }
          level = 1;
          // Change the gamestate
          if(arduboy.pressed(A_BUTTON) and justpressed == 0) {
            justpressed = 1;
            gamestate = 1;
          }
          break;    
    }
  

  if(arduboy.notPressed(A_BUTTON)) {
    justpressed = 0;
  }
  
  arduboy.display();

}
