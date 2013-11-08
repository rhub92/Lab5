#include "game.h"

/*
 * Subroutine Name: initPlayer
 * Author: Capt Branchflower
 * Function: Sets the initial position for the player when the game starts or is reset
 * Inputs: none
 * Outputs: returns an unsigned char of the value of 0x80
 * Subroutines used: none
 */

unsigned char initPlayer() {
	return firstSpaceTopLine;
}

/*
 * Subroutine Name: printPlayer
 * Author: Capt Branchflower
 * Function: Prints the player represented by an asterisk on the LCD screen
 * Inputs: player- the position of the player
 * Outputs: none
 * Subroutines used: writeCommandByte, writeDataByte
 */

void printPlayer(unsigned char player) {
	writeCommandByte(player);
	writeDataByte('*');
}

/*
 * Subroutine Name: clearPlayer
 * Author:Capt Branchflower
 * Function: Clears the player on the LCD screen
 * Inputs: player- the position of the player
 * Outputs: none
 * Subroutines used: writeCommandByte, writeDataByte
 */

void clearPlayer(unsigned char player) {
	writeCommandByte(player);
	writeDataByte(' ');
}

/*
 * Subroutine Name: movePlayer
 * Author: Ryan Hub
 * Function: moves the player on the LCD screen in the direction of up, down, right, or left
 * Inputs: player- the position of the player
 * 		   direction- the direction that the player is about to move in
 * Outputs: returns player- the new position of the player
 * Subroutines used: none
 */

unsigned char movePlayer(unsigned char player, unsigned char direction) {
	switch (direction) {

	case RIGHT:
		if (player == upperRightCorner) {
			player = firstSpaceBottomLine;
		} else {
			player = player + 1;
		}
		break;

	case LEFT:
		if (player == firstSpaceTopLine) {
			player = player;
		} else if (player == firstSpaceBottomLine) {
			player = upperRightCorner;
		} else {
			player = player - 1;
		}
		break;

	case UP:
		if (player <= upperRightCorner) {
			player = player;
		} else {
			player = player - differenceBetweenLines;
		}
		break;

	case DOWN:
		if (player >= firstSpaceBottomLine) {
			player = player;
		} else {
			player = player + differenceBetweenLines;
		}
		break;
	}

	return player;
}

/*
 * Subroutine Name: buttonMove
 * Author: Ryan Hub
 * Function: checks to see which button is pressed and returns that button
 * Inputs: none
 * Outputs: returns button- the button that the user pressed
 * Subroutines used: isP1ButtonPressed, waitforP1ButtonRelease
 */

unsigned char buttonMove() {

	char button = 0;

	if (isP1ButtonPressed(BIT1)) {
		waitForP1ButtonRelease(BIT1);
		button = RIGHT;
	} else if (isP1ButtonPressed(BIT2)) {
		waitForP1ButtonRelease(BIT2);
		button = LEFT;
	} else if (isP1ButtonPressed(BIT3)) {
		waitForP1ButtonRelease(BIT3);
		button = UP;
	} else if (isP1ButtonPressed(BIT4)) {
		waitForP1ButtonRelease(BIT4);
		button = DOWN;
	}

	return button;
}



/*
 * Subroutine Name: printMines
 * Author: Ryan Hub
 * Function: prints the mines to the LCD screen
 * Inputs: mines[]- an array thats size is based on the number of mines
 * Outputs: none
 * Subroutines used: writeCommandByte, writeDataByte
 */

void printMines(unsigned char mines[NUM_MINES]) {
	writeCommandByte(mines[0]);
	writeDataByte('x');
	writeCommandByte(mines[1]);
	writeDataByte('x');
}


/*
 * Subroutine Name: initButtons
 * Author: Ryan Hub
 * Function:intializes the buttons on the geek box
 * Inputs: none
 * Outputs: none
 * Subroutines used: configureP1PinAsButton
 */

void initButtons() {
	configureP1PinAsButton(BIT1 | BIT2 | BIT3 | BIT4);
	P1IES |= BIT1 | BIT2 | BIT3 | BIT4;
	P1IFG &= ~(BIT1 | BIT2 | BIT3 | BIT4);
	P1IE |= BIT1 | BIT2 | BIT3 | BIT4;
}

/*
 * Subroutine Name: timer
 * Author: Ryan Hub
 * Function:intializes the timer for the game
 * Inputs: none
 * Outputs: none
 * Subroutines used: none
 */

void timer() {
	TACTL &= ~(MC1 | MC0);        // stop timer

	TACTL |= TACLR;             // clear TAR

	TACTL |= TASSEL1;   // configure for SMCLK - what's the frequency (roughly)?

	TACTL |= ID1 | ID0; // divide clock by 8 - what's the frequency of interrupt?

	TACTL &= ~TAIFG;            // clear interrupt flag

	TACTL |= MC1;               // set count mode to continuous

	TACTL |= TAIE;              // enable interrupt

}


