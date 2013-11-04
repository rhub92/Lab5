#include "lcd.h"
#include "game.h"
void timer();

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	unsigned char player;
    initSPI();
    lcdInitialize();
    lcdClear();

	buttonInitialize();
	player = initPlayer();
	printPlayer(player);
	//timer();
	while (1) {

		while (player != 0xc7) {
			unsigned char buttonPress = buttonMove();
			player = movePlayer(player, buttonPress);
			printPlayer(player);
		}
		lcdClear();
		displayScreen("You     ");
		goToBottomLine();
		displayScreen("Won!    ");
		buttonMove();
		lcdClear();
		player = initPlayer();
		printPlayer(player);
	}
	while (1) {
	};

}


void timer() {
	TACTL &= ~(MC1|MC0);        // stop timer

	    TACTL |= TACLR;             // clear TAR

	    TACTL |= TASSEL1;           // configure for SMCLK - what's the frequency (roughly)?

	    TACTL |= ID1|ID0;           // divide clock by 8 - what's the frequency of interrupt?

	    TACTL |= ID1|ID0;           // makes it 156k

	    TACTL |= ID1|ID0;           //makes it 19.5k

	    TACTL |= ID1|ID0;			//makes it 244

	    TACTL |= ID1|ID0;			//makes it 30.5

	    TACTL |= ID1|ID0;			//makes it 3.8 hz

	    TACTL |= ID1|ID0;			//makes it ~2 sec

	    TACTL &= ~TAIFG;            // clear interrupt flag

	    TACTL |= MC1;               // set count mode to continuous

	    TACTL |= TAIE;              // enable interrupt

	    __enable_interrupt();       // enable maskable interrupts
}
