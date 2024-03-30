#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // for kbhit() and getch()

#define ROWS 6
#define COLS 6
#define F_ROW 6
#define F_COL 6

struct cartesianTag
{
	// (x, y) 	x for row		y for column
	int x;
	int y;
};

typedef struct cartesianTag cartesian;

// Function to display the grid
void displayGrid(cartesian set_F1[][COLS], cartesian set_F2[][COLS], int nF3_Cardinality, int indexRow, int indexCol, int pos) 
{
    system("cls"); // Clear the screen (Windows specific)
    int i, j;
    
    printf("WELCOME TO THE DSTRU OF DEATH GAME >:)\n");
    printf("press WASD to navigate and press ENTER place your position\n");
    if(pos == 0)
    printf("\nplayer 1 turn\n\n");
    else if(pos == 1)
    printf("\nplayer 2 turn\n\n");

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (i == indexRow && j == indexCol && nF3_Cardinality != 0)
                printf("\t|*|"); // Player position
            else if(set_F1[i][j].x != 0)
                printf("\t|X|"); // Box status
            else if(set_F2[i][j].x != 0)
                printf("\t|O|"); // Box status
            else
            	printf("\t|.|");
            
        }
        printf("\n");
    }
}

int main() {
	cartesian set_F1[F_ROW][F_COL] = {0}, set_F2[F_ROW][F_COL] = {0};
	
    int k = 0;
    int indexRow = 0, indexCol = 0; // Initial player position
	char input;
	
    // Display the initial gridd
    displayGrid(set_F1, set_F2, 1, indexRow, indexCol, k);

    // loop
    do { 
        // Check if a key has been pressed
        if (kbhit()) {
            input = getch(); // Get the pressed key
            switch (input) 
            {
                case 'W':
                case 'w':
                    if (indexRow > 0) 
                        indexRow--;
                    break;
                case 'A':
                case 'a':
                    if (indexCol > 0) 
                    indexCol--;
                    break;
                case 'S':
                case 's':
                    if (indexRow < ROWS - 1) 
                        indexRow++;
                    break;
                case 'D':
                case 'd':
                    if (indexCol < COLS - 1) 
                    indexCol++;
                    break;

                case '\r': // Enter key
                    if (set_F1[indexRow][indexCol].x == 0 && set_F2[indexRow][indexCol].x == 0) 
                    {
                        if (k == 0)
                        {
                        	set_F1[indexRow][indexCol].x = indexRow+1; // Place player position
                        	set_F1[indexRow][indexCol].y = indexCol+1;
                        }
                        else if(k == 1)
                        {
                        	set_F2[indexRow][indexCol].x = indexRow+1; // Place player position
                        	set_F2[indexRow][indexCol].y = indexCol+1;
                        }
                    }
                    if (k == 0)
                    k = 1;
                    else if (k == 1)
                    k = 0;

                    break;
                
                default:
                    break;
            }

            // Display the updated grid
            displayGrid(set_F1, set_F2, 1, indexRow, indexCol, k);
            
        }
    }while (input != '\r');
}
