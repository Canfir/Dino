#include <iostream>
#include <conio.h>

#pragma warning(disable:4996) // POSIX name deprecated

void run();
void printMap();
void initMap();
void move(int dx, int dy);
void update();
void changeDirection(char key);
void clearScreen();
void generateFood();

char getMapValue(int value);

// Map dimensions
const int mapwidth = 20;
const int mapheight = 20;

const int size = mapwidth * mapheight;

// The tile values for the map
int map[size];

// Snake head details
int headxpos;
int headypos;
int direction;

// Amount of food the snake has (How long the body is)
int food = 1;

// Determine if game is running
bool running;

int xe = 0;
int ye = 0;
int s;

int main()
{
	run();
	return 0;
}

// Main game function
void run()
{
	// Initialize the map
	initMap();
	running = true;
	while (running) {
		// If a key is pressed
		if (kbhit()) {
			// Change to direction determined by key pressed
			changeDirection(getch());
		}
		// Upate the map
		update();

		// Clear the screen
		clearScreen();

		// Print the map
		printMap();

		// wait 0.5 seconds
		_sleep(500);
	}

	// Print out game over text
	std::cout << "\t\t!!!Game over!" << std::endl << "\t\tYour score is: " << food;

	// Stop console from closing instantly
	std::cin.ignore();
}

// Changes snake direction from input
void changeDirection(char key) {
	switch (key) {
	case 'w':
		direction = 0;
		break;
	}
}

// Moves snake head to new location
void move(int dx, int dy) {
	// determine new head position
	int newx = headxpos + dx;
	int newy = headypos + dy;

	// Check if there is food at location
	if (map[newx + newy * mapwidth] == -2) {
		// Increase food value (body length)
		s++;

		// Generate new food on map
		generateFood();
	}

	// Check location is free
	/*else if (map[newx + newy * mapwidth] != 0) {
		running = false;
	}*/

	// Move head to new location
	headxpos = newx;
	headypos = newy;
	map[headxpos + headypos * mapwidth] = food + 1;

}

// Clears screen
void clearScreen() {
	// Clear the screen
	system("cls");
}

// Generates new food on map
void generateFood() {
	xe = 0;
	ye = 0;
		// Generate random x and y values within the map
		xe = mapwidth-3;
		ye = mapheight-2;

		// If location is not free try again

	// Place new food
	map[xe + ye * mapwidth] = -2;
}

// Updates the map
void update() {
	// Move in direction indicated
	switch (direction) {
	case 0: move(-1, 0); 
		direction = 1;
		break;
	case 1: move(1, 0);
		direction = 2;
		break;
	case 2: move(0, 0);
		break;
	
	}
	map[xe + ye * mapwidth] = -3;
	xe = xe;
	ye = ye-1;
	if(ye>0) map[xe + ye * mapwidth] = -2;
	else
		generateFood();
	// Reduce snake values on map by 1
	for (int i = 0; i < size; i++) {
		if (map[i] > 0) map[i]--;
	}
}

// Initializes map
void initMap()
{
	// Places the initual head location in middle of map
	headxpos = mapwidth - 2;
	headypos = mapheight / 2;
	map[headxpos + headypos * mapwidth] = 1;

	// Places top and bottom walls
	for (int x = 0; x < mapwidth; ++x) {
		map[x] = -1;
		map[x + (mapheight - 1) * mapwidth] = -1;
	}

	// Places left and right walls
	for (int y = 0; y < mapheight; y++) {
		map[0 + y * mapwidth] = -1;
		map[(mapwidth - 1) + y * mapwidth] = -1;
	}

	// Generates first food
	generateFood();
}

// Prints the map to console
void printMap()
{
	for (int x = 0; x < mapwidth; ++x) {
		for (int y = 0; y < mapheight; ++y) {
			// Prints the value at current x,y location
			std::cout << getMapValue(map[x + y * mapwidth]);
		}
		// Ends the line for next x value
		std::cout << std::endl;
	}
	std::cout << "Vas schet:" << s;
}

// Returns graphical character for display from map value
char getMapValue(int value)
{
	// Returns a part of snake body
	if (value > 0) return 'o';

	switch (value) {
		// Return wall
	case -1: return 'X';
		// Return food
	case -2: return 'O';
	}

	return ' ';
}