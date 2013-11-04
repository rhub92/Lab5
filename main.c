#include "lcd.h"
#include "game.h"


void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	unsigned char player;
    initSPI();
    lcdInitialize();
    lcdClear();

    player = initPlayer();
    printPlayer(player);

    buttonInitialize();

    while(1){
    	unsigned char buttonPress = buttonMove();
    	player = movePlayer(player, buttonPress);
    	printPlayer(player);
   }
while(1){};

}
