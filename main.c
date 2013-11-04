#include "lcd.h"
#include "game.h"


void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    initSPI();
    lcdInitialize();
    lcdClear();

    printPlayer(initPlayer());


while(1){};

}
