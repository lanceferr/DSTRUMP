#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // for kbhit() and getch()

#define ROWS 6
#define COLS 6

// Function to display the grid
void displayGrid(char F[ROWS][COLS], int indexRow, int indexCol, int pos) 
{
    system("cls"); // Clear the screen (Windows specific)
    int i, j;
    
    printf("WELCOME TO THE DSTRU OF DEATH GAME >:)\n");
    printf("press WASD to navigate and press ENTER place your position\n");
    if(pos == 0)
    printf("\nplayer 1 turn\n");
    else if(pos == 1)
    printf("\nplayer 2 turn\n");

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (i == indexRow && j == indexCol)
                printf("|*|\t"); // Player position
            else
                printf("|%c|\t", F[i][j]); // Box status
        }
        printf("\n");
    }
}

int main() {
    char F[ROWS][COLS]; // Grid to store box status
    int i, j, k = 0, l = 1;
    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            F[i][j] = '.'; // Initialize all boxes as empty
        }
    }

    int indexRow = 0, indexCol = 0; // Initial player position

    // Display the initial gridd
    displayGrid(F, indexRow, indexCol, k);

    // Game loop
    char input;
    while (l == 1) { 
        // Check if a key has been pressed
        if (kbhit()) {
            input = getch(); // Get the pressed key
            switch (input) 
            {
                case 'W':
                case 'w':
                    if (indexRow > 0 && F[indexRow - 1][indexCol]) 
                        indexRow--;
                    break;
                case 'A':
                case 'a':
                    if (indexCol > 0 && F[indexRow][indexCol - 1]) 
                    indexCol--;
                    break;
                case 'S':
                case 's':
                    if (indexRow < ROWS - 1 && F[indexRow + 1][indexCol]) 
                        indexRow++;
                    break;
                case 'D':
                case 'd':
                    if (indexCol < COLS - 1 && F[indexRow][indexCol + 1]) 
                    indexCol++;
                    break;

                case '\r': // Enter key
                    if (F[indexRow][indexCol] != 'X' && F[indexRow][indexCol] != 'O') 
                    {
                        if (k == 0)
                        F[indexRow][indexCol] = 'X'; // Place player position
                        else if(k == 1)
                        F[indexRow][indexCol] = 'O';
                    }
                    if (k == 0)
                    k = 1;
                    else if (k == 1)
                    k = 0;

                    break;
                case 'q':
                    l = 0; // Quit the program
                    break;
                default:
                    break;
            }

            // Display the updated grid
            displayGrid(F, indexRow, indexCol, k);
            
        }
    }

    return 0;
}
