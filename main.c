/*
* Lab 5: A Simple Game
*
* Author: Ryan Hub
*
* Date: 07 November 2013
*
* Purpose: The purpose of this lab is to create a simple game that utilizes the buttons and LCD screen on the geek box. The user has to use buttons
* that represents up, down, left, and right to move an asterisk from the top left corner of the LCD screen to the bottom right corner of the LCD
* screen. If the user does not press a button within 2 seconds the player loses and the game is over. The user can also lose if they hit a mine which
* are randomly printed on the screen at the start of each new game.
*
* Documentation: I acknowledge help from Captain Branchflower for helping me with B functionality and getting me started with the random numbers, c2c
* Colin Busho for helping me get started on the timer system, and c2c Jason Mossing for helping me get started on B functionality
*/

#include "lcd.h"
#include "game.h"


unsigned char game;
char buttons[] = { BIT1, BIT2, BIT3, BIT4 };
char flag = 0;
unsigned char player;
unsigned char mines[NUM_MINES];
char button;

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	//Initializes the LCD screen
	initSPI();
	lcdInitialize();
	lcdClear();

	timer();
	initButtons();
	_enable_interrupt(); //enable maskable interrupts

	//Initializes the random numbers that will be used for generating the mines
	unsigned int seed = 2874;
	unsigned int random = prand(seed);

	while (1) {
		//Creates the mines and makes sure they are not on top or diaganol to each other and then prints the mines to the screen
		mines[0] = firstSpaceTopLine;
		mines[1] = firstSpaceBottomLine;
		while (mines[1] - mines[0] == differenceBetweenLines || mines[1] - mines[0] == differenceBetweenLines + 1
				|| mines[1] - mines[0] == differenceBetweenLines - 1) {
			random = prand(random);
			mines[0] = firstSpaceTopLine + 1 + random % 7;
			random = prand(random);
			mines[1] = firstSpaceBottomLine + random % 7;
		}
		printMines(mines);

		player = initPlayer();
		printPlayer(player);
		game = 1;
		while (player != playerWon && game != 0 && player != mines[0]
				&& player != mines[1]) {
		}

		//Excecutes the code below if the player wins the game
		if (player == playerWon) {
			lcdClear();
			displayScreen("You     ");
			goToBottomLine();
			displayScreen("Won!    ");
			button = pollP1Buttons(buttons, 4);
			while (!(button & P1IN)) {}
			debounce();
			lcdClear();
			//Resets the timer
			TACTL |= TACLR;
			flag = 0;

			//Executes the code below if the timer reaches 2 seconds
		} else if (game == 0) {
			game = 1;
			lcdClear();
			displayScreen("You     ");
			goToBottomLine();
			displayScreen("Lose!   ");
			char loseButton;
			loseButton = pollP1Buttons(buttons, 4);
			while (!(loseButton & P1IN)) {}
			debounce();
			lcdClear();
			TACTL |= TACLR;
			flag = 0;

			//Executes the code below if the player hits a mine
		} else if (player == mines[0] || player == mines[1]) {
			lcdClear();
			displayScreen("BOOOOOOM");
			goToBottomLine();
			displayScreen("YOU DEAD");
			button = pollP1Buttons(buttons, 4);
			while (!(button & P1IN)) {}
			debounce();
			lcdClear();
			TACTL |= TACLR;
			flag = 0;
			game = 1;
		}
	}
}

/*
 * Subroutine Name: testAndRespondToButtonPush
 * Author: Ryan Hub
 * Function: Switches the edge that the button is read on
 * Inputs: buttonToTest- the button that the user pressed
 * Outputs: none
 * Subroutines used: clearPlayer, movePlayer, printPlayer, debounce
 */

void testAndRespondToButtonPush(char buttonToTest) {
	if (buttonToTest & P1IFG) {
		if (buttonToTest & P1IES) {
			clearPlayer(player);
			player = movePlayer(player, buttonToTest);
			printPlayer(player);
			TACTL |= TACLR;
			flag = 0;
		} else {
			debounce();
		}

		// Switches the edge the button will be read on
		P1IES ^= buttonToTest;
		P1IFG &= ~buttonToTest;
	}
}

//Represents the timer so every half second flag is incremented by one, and once flag equals four then it sets the variable 'game' to 0
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR() {
	TACTL &= ~TAIFG;            // clear interrupt flag
	flag += 1;
	// 1 flag represents half a second, so once flag equals 4 the 2 second timer runs out and the player loses
	if (flag == 4) {
		game = 0;
	}
}

//Handles button presses via interrupts and uses the subroutine 'testAndRespondToButtonPush' to switch the edge that the button press is read on
#pragma vector = PORT1_VECTOR
__interrupt void Port_1_ISR() {
	//Switches the edge the button is read on while the game is running
	if (game != 0) {
		testAndRespondToButtonPush(BIT1);
		testAndRespondToButtonPush(BIT2);
		testAndRespondToButtonPush(BIT3);
		testAndRespondToButtonPush(BIT4);
	}
}
