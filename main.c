#include "lcd.h"
#include "game.h"
void timer();


char flag = 0;
unsigned char player;
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    initSPI();
    lcdInitialize();
    lcdClear();


    timer();
	buttonInitialize();
	_enable_interrupt();
	while (1) {
		player = initPlayer();
		printPlayer(player);

		//could also include in while if some value is 1 and when you lose the value is set to zero
		while (player != 0xc7) {
			unsigned char buttonPress = buttonMove();
			clearPlayer(player);
			player = movePlayer(player, buttonPress);
			printPlayer(player);
			TACTL |= TACLR;
			flag = 0;
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
	//while (1) {
	//};

}


void timer() {
	TACTL &= ~(MC1|MC0);        // stop timer

	    TACTL |= TACLR;             // clear TAR

	    TACTL |= TASSEL1;           // configure for SMCLK - what's the frequency (roughly)?

	    TACTL |= ID1|ID0;           // divide clock by 8 - what's the frequency of interrupt?

	    TACTL &= ~TAIFG;            // clear interrupt flag

	    TACTL |= MC1;               // set count mode to continuous

	    TACTL |= TAIE;              // enable interrupt

	    __enable_interrupt();       // enable maskable interrupts

}
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR()
{
    TACTL &= ~TAIFG;            // clear interrupt flag
    flag += 1;
	if (flag == 4) {
		lcdClear();
		displayScreen("You     ");
		goToBottomLine();
		displayScreen("Lose!   ");
		buttonMove();
		lcdClear();
		player = initPlayer();
		printPlayer(player);
    }
}
