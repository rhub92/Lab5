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
	switch (direction) {
		//
		// update player position based on direction of movement
		//
	}

	return player;
}

char didPlayerWin(unsigned char player)
{
	return player == 0xC7;
}





