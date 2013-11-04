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
	while ((BIT1 & P1IN) && (BIT2 & P1IN) && (BIT3 & P1IN) && (BIT4 & P1IN)) {
		if (BIT1 & ~P1IN) {
			return RIGHT;
		}

		if (BIT2 & ~P1IN) {
			return LEFT;
		}

		if (BIT3 & ~P1IN) {
			return UP;
		}

		if (BIT4 & ~P1IN) {
			return DOWN;
		}
	}
}



