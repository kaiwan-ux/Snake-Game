//============================================================================
// Name        : Tetris.cpp
// Author      : 
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Tetris...
//============================================================================
#ifndef TETRIS_CPP_                  // All the libraries are present here
#define TETRIS_CPP_
#include "util.h"                    
#include <iostream>                  // For cout and cin statement
#include<vector>                     // For arithmetic functions
#include<algorithm>                  // For different functions
//#include<cstdlib>
#include<ctime>                      // For date and time operation
#include<string>                     // To create string of words 
//#include<sys/wait.h>
//#include<stdlib.h>
//#include<stdio.h>
#include<unistd.h>
#include<sstream>                    // to store sting and used in file handling
#include<cmath>                      // different functions like cos sine etc basic functions


using namespace std;                // name space function to 


       // Deceleration of the different variables 
       
 const int maxSegments = 50;                           // Its the number of segment or parts  of snake
 int snakeX[maxSegments], snakeY[maxSegments];         // To store the X and Y components of snake segment array is used 
 int snakeLength = 3;                                  // first length of the snake in the game
 int snakeDirection = 0;                               // supposing the directions of the snake  (0: UP, 1: DOWN, 2: RIGHT, 3: LEFT)
 int segmentSize = 20;                                 // Supposing the  size of each segment of the snake
 int width = 650, height = 650;                        // Dimension of the screen
 int foodX[5] , foodY[5];                              // position of food 
 int lineWidth = 5;                                    // Width of the line 
 int score = 0;                                        // Initial score of the game 
 int powerfoodX= 0, powerfoodY = 0;                    // Power food initialization 
 bool hasPowerFood = false;                            // command to check condition either it is true or false 
 int powerFoodSize = 30;                               //  size of power food 
 int powerFoodTimer = 10;                              // time for the power food appearance 


// function to generate the power food in the snake game 

 void PowerFoodFormation() {
    powerfoodX = (rand() % (width / segmentSize)) * segmentSize;      // For X component
    powerfoodY= (rand() % (height / segmentSize)) * segmentSize;      // For Y component
}

 // function to manage the power food in the code 
 
 void HandelingPowerFood(int m) {
    if (!hasPowerFood) {                         // if checking condition 
        PowerFoodFormation();
        hasPowerFood = true;                     // checking for generation of power food 
        glutPostRedisplay();
    }
}

 // Function for checking collision of snake
 
 void CollisionChecking() {
 
    for(int i=0;i<5;i++)                        // Loop for generation of five random foods 
    
  // Condition for checking the collision of snake with the random food 
{
   if (sqrt(pow(snakeX[0] - foodX[i], 2) + pow(snakeY[0] - foodY[i], 2)) <= segmentSize) {
        
        snakeLength++;                          // snake length increase
        score += 5;                             // Score increases after hitting the snake head with the food 
        
        // Generation of food after eating of food 
        foodX[i] = (rand() % (width / segmentSize)) * segmentSize;
        foodY[i] = (rand() % (height / segmentSize)) * segmentSize;

                                                // Generate power food after eating regular food item in the game 
        glutTimerFunc(powerFoodTimer * 1000, HandelingPowerFood, 0);
    } 
    
    }
        // For the power food eaten 
        
    if (hasPowerFood && sqrt(pow(snakeX[0] - powerfoodX, 2) + pow(snakeY[0] - powerfoodY, 2)) <= powerFoodSize) {
        
        score += 20;                // Increase in score item 
        snakeLength++;              // Increase in the length of the snake
        hasPowerFood = false;
                                    // Appearance of power food after 30 seconds 
        glutTimerFunc(80000, HandelingPowerFood, 0);
    }
  
}
        // checking condition of collision with the walls 

bool CollisionWithWall(int x, int y) {
    return (x >= width || x < 0 || y >= height || y < 0);
}
        // Checking collision of snake with the itself
bool CollisionWithItself(int x, int y) {

    for (int i = 1; i < snakeLength; ++i) {
    
        if (snakeX[i] == x && snakeY[i] == y) {
        
            return true;
        }
    }
    return false;
}
        //Condition when the two upper condition or any one becomes true the game is over and every thing set to its starting point
        
bool GameOver() {

    bool wallCollision = CollisionWithWall(snakeX[0], snakeY[0]);
    bool selfCollision = CollisionWithItself(snakeX[0], snakeY[0]);

    return wallCollision || selfCollision;
}

        // Function to handle the game over condition and every thing becomes initial again
        
 void handleGameOver() {
    if (GameOver()) {             // if condition for the checking 
        snakeLength = 3;
        score = 0;
        snakeX[0] = width / 2;
        snakeY[0] = height / 2;
        snakeDirection = 0;
    }
   
}
      // Function for the continuously movement of the snake 
      
      
void MoveSnake() 
{
   int i = snakeLength - 1;
   
while (i > 0) {                        // while condition for coordinates movement 

    snakeX[i] = snakeX[i - 1];
    
    snakeY[i] = snakeY[i - 1];
    
    i--;
}
if (snakeDirection == 0) { // For upward movement of snake 

    snakeY[0] += segmentSize;
    
} else if (snakeDirection == 1) { // For downward movement of snake 

    snakeY[0] -= segmentSize;
    
} else if (snakeDirection == 2) { // For right movement of snake 

    snakeX[0] += segmentSize;
    
} else if (snakeDirection == 3) { // For left movement of snake 

    snakeX[0] -= segmentSize;
}

CollisionChecking();                 // Calling of check collision function
                                  
 handleGameOver();                   // calling of handle game over function
  }
  
      // Function to adjust the size of the canvass 
      
void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    
    glOrtho(0, width, 0, height, -1, 1); // For the setting of the screen size
    
    glMatrixMode( GL_MODELVIEW);
    
    glLoadIdentity();
}
      // Function for the view of the score of the game in the text form 
      
void ScoreText(int score) {
    
    glColor3f(1.0, 1.0, 1.0);         // Set color to white of the given text

                                      // Giving position to the score display on the top right corner 
    float posX = width - 100;
    
    float posY = height - 20;

                                     // Generate the string for rendering the score 
    string scoreText = "SCORE: " + to_string(score);

    glRasterPos2f(posX, posY);       // giving the text a position in the game 
    for (char c : scoreText) {
    
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c); // Render each character of the score
    }
}

 
  // Display function to display every thing in the snake game 

void Display(){

    glClearColor(0, 0, 0, 0);                            // giving a black color to the background 
 
    glClear(GL_COLOR_BUFFER_BIT);

    int gridSize = 25;                               // grid cell size in the game display
    
    int screenWidth = glutGet(GLUT_WINDOW_WIDTH);    // Adjusting the width of the window screen
    
    int screenHeight = glutGet(GLUT_WINDOW_HEIGHT);  // Adjusting the height of the window screen

    // Drawing of the  grid lines on the snake display
    
    glColor3f(1.0, 1.0, 1.0);                        // Setting the line color to white
    
    glLineWidth(1);                                 // Adjusting the line width for formation of grid lines 

    glBegin(GL_LINES);
    
   int i = 0;
   while (i <= screenWidth) {

    glVertex2f(i, 0); // starting of vertical lines from up to down
    
    glVertex2f(i, screenHeight);
    
    i = i + gridSize;
}

   int j = 0;
   while (j <= screenHeight) {

    glVertex2f(0, j);   // Starting of the horizontal line from left to right 
    
    glVertex2f(screenWidth, j);
    j = j + gridSize;
}
    glEnd();
    
  //Recalling of the snake function 
  
    MoveSnake();
    
   // for loop for the generation of the food 
   
    for(int i=0;i<5;i++)
    {
    // For the display of the simple food on the screen in the snake game 
    
if (foodX[i] == 0 && foodY[i] == 0) {

       foodX[i] = (rand() % (width / segmentSize)) * segmentSize;
       
        foodY[i] = (rand() % (height / segmentSize)) * segmentSize;
    }
    

    // Drawing the food at the X and Y points 
    
  glColor3f(1.0, 0.0, 0.0); // Adjusting the color of the food 
  
                            // Generation of the food
                            
    DrawSquare(foodX[i], foodY[i], segmentSize, colors[10]);

}
        // For the display of the power food on the screen in the snake game 
    
    if (hasPowerFood) {
        // Drawing the power food at the power food X and Y coordinates 
        
        glColor3f(0.0, 1.0, 0.0); // Adjusting the color of the power food 
        
        DrawSquare(powerfoodX, powerfoodY, powerFoodSize, colors[2]); // Generation of the  power food

        //  The if condition for the Checking of  collision with power food
        
        if (sqrt(pow(snakeX[0] - powerfoodX, 2) + pow(snakeY[0] - powerfoodY, 2)) <= powerFoodSize) {
            // Increase score by 20
            score += 20;
            hasPowerFood = false;
        }
    }

    // Redrawing of the snake position after rendering
    
   for (int i = 0; i < snakeLength; ++i) {
    
        if (i == 0) {
        
            DrawCircle(snakeX[i] + segmentSize / 2, snakeY[i] + segmentSize / 2, (segmentSize)*0.65, colors[3]);
        } else {
            DrawSquare(snakeX[i], snakeY[i], segmentSize, colors[3]); // Draw the snake's segments
        }
    }
    
      // recalling of score function in the display
      
    ScoreText(score);

    glutSwapBuffers();
}


 void NonPrintableKeys(int key, int x, int y) {
 
   if (key == GLUT_KEY_LEFT) {
   
    snakeDirection = 3; // for left direction
    
} else if (key == GLUT_KEY_RIGHT) {

    snakeDirection = 2;// for right direction
    
} else if (key == GLUT_KEY_UP) {

    snakeDirection = 0; // for upward direction
    
} else if (key == GLUT_KEY_DOWN) {
    snakeDirection = 1; // for downward direction

} else {

    //  for the Default case
}

    // This function calls the Display function to redo the drawing in the snake game 
    
    glutPostRedisplay();
}

    // function to call the operation immediately by a single clicking of the button
    
void PrintableKeys(unsigned char key, int x, int y) {

    if (key == KEY_ESC) {
    
        exit(1); // exit the program when escape key is pressed.
    }
    if (key == 'R' || key=='r') {
    
    }
  
   
    glutPostRedisplay();
}


 // The function to control the time in the given snake game thats why it is called as timer function

 void Timer(int m) {

 glutPostRedisplay();

//  to call our Timer function after given time interval
 
    glutTimerFunc(500.0 / FPS, Timer, 0);
 }


 
 
int main(int argc, char*argv[]) {

    int width = 650, height = 650;   // initializing the length and width of the window screen 
    
    InitRandomizer(); // it usually generate the random number 
    
    glutInit(&argc, argv); // for  the graphics library...

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // For using the color display mode
    
    glutInitWindowPosition(50, 50); // Command for setting the size of the initial window
    
    glutInitWindowSize(width, height); // For setting the size of our window
    
    glutCreateWindow("PF's Snake Game"); //  for set the title of our game window
    
    SetCanvasSize(width, height); // This command is used for setting the number of pixels in the game 
    
    glutDisplayFunc(Display); // for drawing canvas as a display it calls the function
    
    glutSpecialFunc(NonPrintableKeys); // function to call for non-printable ASCII characters
    
    glutKeyboardFunc(PrintableKeys); // function to call for printable ASCII characters
                                    
    glutTimerFunc(1000.0 / FPS, Timer, 0);// function to call out the timer after every interval



    glutMainLoop();
    
    return 1;
}
#endif /* Snake Game */




	

