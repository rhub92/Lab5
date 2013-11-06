#include "lcd.h"
#include "game.h"
void timer();

unsigned char game;
char buttons[] = { BIT1, BIT2, BIT3, BIT4 };
char flag = 0;
unsigned char player;
unsigned char mines[NUM_MINES];
char button;

void initButtons()
{
	configureP1PinAsButton(BIT1 | BIT2 | BIT3 | BIT4);
	P1IES |= BIT1|BIT2|BIT3|BIT4;
	P1IFG &= ~(BIT1|BIT2|BIT3|BIT4);
	P1IE |= BIT1|BIT2|BIT3|BIT4;
}

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	initSPI();
	lcdInitialize();
	lcdClear();

	timer();
	initButtons();
	_enable_interrupt();
	unsigned int seed = 2874;
	unsigned int random = prand(seed);
	while (1) {

		mines[0] = 0x80;
		mines[1] = 0xc0;

		while (mines[1] - mines[0] == 0x40 || mines[1] - mines[0] == 0x41
				|| mines[1] - mines[0] == 0x3f) {
			random = prand(random);
			mines[0] = 0x81 + random % 7;
			random = prand(random);
			mines[1] = 0xc0 + random % 7;
		}
		printMines(mines);

		player = initPlayer();
		printPlayer(player);
		//could also include in while if some value is 1 and when you lose the value is set to zero

		game = 1;
		//while (game != 0) {
		while (player != 0xc7 && game != 0 && player != mines[0]
				&& player != mines[1]) {
		}
		if (player == 0xc7) {
			lcdClear();
			displayScreen("You     ");
			goToBottomLine();
			displayScreen("Won!    ");
			button = pollP1Buttons(buttons, 4);
			while (!(button & P1IN)) {}
			debounce();
			lcdClear();
			TACTL |= TACLR;
			flag = 0;
			//player = initPlayer();
			//printPlayer(player);
		} else if(game == 0) {
			//__disable_interrupt();
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
			//player = initPlayer();
			TACTL |= TACLR;
			flag = 0;
			//printPlayer(player);
			//generateMines(mines);
			//__enable_interrupt();
		} else if (player == mines[0] || player == mines[1]) {
			lcdClear();
			displayScreen("BOOOOOOM");
			goToBottomLine();
			displayScreen("YOU DEAD");
			button = pollP1Buttons(buttons, 4);
			while (!(button & P1IN)) {}
			debounce();
			lcdClear();
			//player = initPlayer();
			TACTL |= TACLR;
			flag = 0;
		}
	}
}



void timer() {
	TACTL &= ~(MC1|MC0);        // stop timer

	    TACTL |= TACLR;             // clear TAR

	    TACTL |= TASSEL1;           // configure for SMCLK - what's the frequency (roughly)?

	    TACTL |= ID1|ID0;           // divide clock by 8 - what's the frequency of interrupt?

	    TACTL &= ~TAIFG;            // clear interrupt flag

	    TACTL |= MC1;               // set count mode to continuous

	    TACTL |= TAIE;              // enable interrupt

	    //__enable_interrupt();       // enable maskable interrupts

}

void testAndRespondToButtonPush(char buttonToTest)
{
    if (buttonToTest & P1IFG)
    {
        if (buttonToTest & P1IES)
        {
        	//buttonToTest = buttonMove();
        	clearPlayer(player);
        	player = movePlayer(player, buttonToTest);
        	printPlayer(player);
        	//movePlayerInResponseToButtonPush(buttonToTest);
			TACTL |= TACLR;
			flag = 0;
        } else
        {
            debounce();
        }

        P1IES ^= buttonToTest;
        P1IFG &= ~buttonToTest;
    }
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR()
{
    if(flag < 4){
	TACTL &= ~TAIFG;            // clear interrupt flag
    flag += 1;
	clearPlayer(mines[0]);
	clearPlayer(mines[1]);
    mines[0] = mines[0] - 1;
	mines[1] = mines[1] - 1;
	printMines(mines);
    }
	if (flag == 4) {
		game = 0;
	}
}
#pragma vector = PORT1_VECTOR
__interrupt void Port_1_ISR(){
	if(game != 0) {
        testAndRespondToButtonPush(BIT1);
        testAndRespondToButtonPush(BIT2);
        testAndRespondToButtonPush(BIT3);
        testAndRespondToButtonPush(BIT4);
	}
}
