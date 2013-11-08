/*
 * game.h
 * Author: Todd Branchflower
 *
 * This is shell code for the game to be implemented in Lab 4.  It provides basic functions that may prove useful in accomplishing the lab.
 */
#include "msp430-rng/rand.h"
#include "buttons/button.h"
#include "lcd.h"
#include <msp430g2553.h>

/* LCG constants */
#define M 49381                               // Multiplier
#define I 8643                                // Increment
#define RIGHT BIT1
#define LEFT BIT2
#define UP BIT3
#define DOWN BIT4
#define ROW_MASK 0x40
#define playerWon 0xc7
#define firstSpaceTopLine 0x80
#define firstSpaceBottomLine 0xc0
#define upperRightCorner 0x87
#define differenceBetweenLines 0x40

#define NUM_MINES 2

//
// Initializes player to starting position on board.
//
unsigned char initPlayer();

//
// Prints the player marker (*) at the player location passed in.
//
void printPlayer(unsigned char player);

//
// Clears the location passed in.
//
void clearPlayer(unsigned char player);

//
// Given a player's current position and a direction, returns an updated player position.
//
unsigned char movePlayer(unsigned char player, unsigned char direction);

//
// Returns true if the position passed in is the winning game position.
//
char didPlayerWin(unsigned char player);

//Returns the button that the user pressed

unsigned char buttonMove();

//Function to return a pseudo random number

unsigned int prand(unsigned int state);

//Generates random mines to be placed on the LCD screen

void generateMines(unsigned char mines[NUM_MINES]);

//Prints the random mines on the LCD screen

void printMines(unsigned char mines[NUM_MINES]);

//Initializes the buttons on the geek box

void initButtons();

//Intializes the timer for the game

void timer();
