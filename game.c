#include <msp430g2553.h>
#include "game.h"
#include "lcd.h"



unsigned char initPlayer()
{
	return 0x80;
}

void printPlayer(unsigned char player)
{
	writeCommandByte(player);
	writeDataByte('*');
}

void clearPlayer(unsigned char player)
{
	writeCommandByte(player);
	writeDataByte(' ');
}

unsigned char movePlayer(unsigned char player, unsigned char direction)
{
	//clearPlayer(player);
	switch (direction) {
	case RIGHT:
		if (player == 0x87) {
			player = 0xc0;
		} else {
		player = player + 1;
		}
		break;

	case LEFT:
		if (player == 0x80) {
			player = player;
		} else if (player == 0xc0) {
			player = 0x87;
		} else {
		player = player - 1;
		}
		break;

	case UP:
		if (player <= 0x87) {
			player = player;
		} else {
			player = player - 0x40;
		}
		break;

	case DOWN:
		if(player >= 0xc0) {
			player = player;
		} else {
			player = player + 0x40;
		}
		break;
	}

	return player;
}

//unsigned char didPlayerWin(unsigned char player)
//{
	//return player == 0xC7;
//}

unsigned char buttonMove() {

	char button;

	while ((BIT1 & P1IN) && (BIT2 & P1IN) && (BIT3 & P1IN) && (BIT4 & P1IN)) {
	//if(isP1ButtonPressed(BIT1)) {
	if (BIT1 & ~P1IN) {
			button = RIGHT;
	}

	//if(isP1ButtonPressed(BIT2)){
		if (BIT2 & ~P1IN) {
			button = LEFT;
	}
	//if(isP1ButtonPressed(BIT3)){
		if (BIT3 & ~P1IN) {
			button = UP;
	}
	//if(isP1ButtonPressed(BIT4)) {
		if (BIT4 & ~P1IN) {
			button = DOWN;
	}
	}


	return button;
}


void generateMines(unsigned char mines[NUM_MINES]) {
	int seed = rand();
	mines[0] = 0x80;
	mines[1] = 0xc0;

	while(mines[1] - mines[0] == 0x40 || mines[1] - mines[0] == 0x41 || mines[1] - mines[0] == 0x39){
		int random = prand(seed);
		int random1 = prand(random);
		mines[0] = 0x81 + random%7;
		mines[1] = 0xc0 + random1%7;
		printMines(mines);
	}
}

void printMines(unsigned char mines[NUM_MINES]) {
	writeCommandByte(mines[0]);
	writeDataByte('x');
	writeCommandByte(mines[1]);
	writeDataByte('x');
}
