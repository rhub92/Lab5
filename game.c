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
	clearPlayer(player);
	switch (direction) {
	case 1:
		if (player == 0x87) {
			player = 0xc0;
		} else {
		player = player + 1;
		}
		break;

	case 2:
		if (player == 0x80) {
			player = player;
		} else {
		player = player - 1;
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
	while ((BIT1 & P1IN) && (BIT2 & P1IN) && (BIT3 & P1IN)) {
	if(BIT1 & P1IN) {
		return 1;
	}

	if(BIT2 & P1IN) {
		return 2;
	}
}
}



