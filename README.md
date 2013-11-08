Lab5
====

Contains the necessary code to create a game of a player represented by an asterisk that has to move across the screen
by using buttons whithout hitting a mine and the time between button presses has to be less than 2 seconds or the game 
is over. This game requires previous code from the LCD library which is included in game.h. The buttons library is
included as well, and a function that is used to generate random numbers. 

Code:

unsigned char initPlayer(): Used to set the initial position for the player

void printPlayer(unsigned char player): Prints the player represented by an asterisk on the LCD screen

void clearPlayer(unsigned char player): Clears the player from the LCD screen

unsigned char movePlayer(unsigned char player, unsigned char direction): Given a player's
current position and a direction, returns an updated player position.

char didPlayerWin(unsigned char player):  Returns true if the position passed in is the winning game position.

unsigned char buttonMove(): Returns the button that the user pressed

unsigned int prand(unsigned int state): Function to return a pseudo random number

void generateMines(unsigned char mines[NUM_MINES]): Generates random mines to be placed on the LCD screen

void printMines(unsigned char mines[NUM_MINES]): Prints the random mines on the LCD screen

void initButtons(): Initializes the buttons on the geek box

void timer(): Intializes the timer for the game
