
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define FALSE (0)
#define TRUE (!(FALSE))

#define C_ROW 2
#define C_COL 2

#define F_ROW 6
#define F_COL 6

#define P_ROW 2
#define P_COL 2

#define S_ROW 4
#define S_COL 6


typedef int Boolean; // either TRUE or FALSE

struct cartesianTag
{
	// (x, y) 	x for row		y for column
	int x;
	int y;
};

typedef struct cartesianTag cartesian;


// insert function prototypes

int getSet_F3(cartesian [][F_COL], cartesian [][F_COL], cartesian [][F_COL]);
Boolean isOver(cartesian [][C_COL], cartesian [][C_COL], cartesian [][F_COL], cartesian [][P_COL], int);
void addElement_F(cartesian *, cartesian [][F_COL]);
void addElement_C(cartesian *, cartesian [][C_COL]);
int getPatternsCompleted(cartesian [][F_COL]);
int getCardinality_C(cartesian [][C_COL]);
void displayGrid(cartesian [][F_COL], cartesian [][F_COL], Boolean, int, int, int);
void navigateGrid(cartesian [][F_COL], cartesian [][F_COL], int, int *, int *, cartesian *, Boolean);


int
main()
{
	
	// definition of sets P and S from MP specs
	cartesian set_P[P_ROW][P_COL] = {{{1,1}, {2,2}},  {{1,2}, {2,1}}};
	
	cartesian set_S[S_ROW][S_COL] = {{{1,1}, {1,3}, {2,2}, {3,1}, {3,3}},
									 {{4,4}, {4,6}, {5,5}, {6,4}, {6,6}},
									 {{1,5}, {2,4}, {2,5}, {2,6}, {3,5}},
									 {{4,1}, {4,3}, {5,1}, {5,3}, {6,1}, {6,3}}};
		
	// other sets definitions
	cartesian set_C1[C_ROW][C_COL] = {0}, set_C2[C_ROW][C_COL] = {0};
	cartesian set_F1[F_ROW][F_COL] = {0}, set_F2[F_ROW][F_COL] = {0}, set_F3[F_ROW][F_COL] = {0};

	// pos definition
	// (a, b)
	cartesian pos = {0};
	
	// (c, d)
	cartesian quad_pos = {0};
	
	int indexRow = 0;
	int indexCol = 0;
	
	// other variable declarations
	Boolean good = FALSE;
	Boolean over = FALSE;
	Boolean next = FALSE;

	int nF3_Cardinality = getSet_F3(set_F1, set_F2, set_F3);
	int nF1_PatternCompleted;
	int nF2_PatternCompleted;
	
	int nC1_Cardinality;
	int nC2_Cardinality;
	
	char results[7];
	
	// for value checking
	printf("Set P:\n");
	for(int i=0; i<P_ROW; i++)
	{
		for(int j=0; j<P_COL; j++)
			printf("(%d, %d)\t", set_P[i][j].x, set_P[i][j].y);
		printf("\n");
	}
	
	printf("\n\nSet S:\n");
	for(int i=0; i<S_ROW; i++)
	{
		for(int j=0; j<S_COL; j++)
			printf("(%d, %d)\t", set_S[i][j].x, set_S[i][j].y);
			
	printf("\n");
	}
	
	
//	addElement_F(&set_P[0][0], set_F1);
//	addElement_F(&set_P[0][1], set_F1);
//	
//	addElement_F(&set_P[1][0], set_F2);
//	addElement_F(&set_P[1][1], set_F2);
//	
//	nF3_Cardinality = getSet_F3(set_F1, set_F2, set_F3);
//	
//	printf("\n\nSet F3:\n");
//	for(int i=0; i<F_ROW; i++)
//	{
//		for(int j=0; j<F_COL; j++)
////			printf("(%d, %d)\t", set_F3[i][j].x, set_F3[i][j].y);
//			if(set_F3[i][j].x == 0)
//				printf("0\t");
//			else
//				printf("1\t");
//			
//	printf("\n\n");
//	}
	// end of value checking
	
	

		
	do	
	{
		
	//	NextPlayerMove (prototype)
		
		navigateGrid(set_F1, set_F2, over, &indexRow, &indexCol, &pos, next);
		
		// get (c,d)		
		quad_pos.x = (pos.x-1)/3 +1;
		quad_pos.y = (pos.y-1)/3 +1;

		// then...
		
//		if(!over && next && (set_F3[pos.x+1][pos.y+1].x != 0 ) )
//		{
//			good = !good;
//			addElement_F(&pos, set_F1);
//		}
//		
//		else if(!over && !next && (set_F3[pos.x+1][pos.y+1].x != 0 ) )
//		{
//			good = !good;
//			addElement_F(&pos, set_F2);
//		}		
		
		nF3_Cardinality = getSet_F3(set_F1, set_F2, set_F3);
		
		// get cardinality of the (power set of set_F1) union (set_S)	possible results: 1-4
		// get cardinality of the (power set of set_F2) union (set_S)	possible results: 1-4
		nF1_PatternCompleted = getPatternsCompleted(set_F1);
		nF2_PatternCompleted = getPatternsCompleted(set_F2);
		
		// get cardinality of set_C1	possible results: 1-4
		// get cardinality of set_C2	possible results: 1-4
		nC1_Cardinality = getCardinality_C(set_C1);
		nC2_Cardinality = getCardinality_C(set_C2);
		
		if(!over /*&& good*/ && next && (nF1_PatternCompleted > nC1_Cardinality))
			addElement_C(&quad_pos, set_C1);
			
		else if(!over /*&& good*/ && !next && (nF2_PatternCompleted > nC2_Cardinality))
			addElement_C(&quad_pos, set_C2);
			
		
		if(!over && good )
			good = !good;
		
		
		over = isOver(set_C1, set_C2, set_F3, set_P, nF3_Cardinality);
		
	// GameOver (prototype)	
		
		if(over && next && set_C1[0][0].x != 0 && set_C1[1][1].x != 0)
			strcpy(results, "A wins");
		else if(over && next && set_C1[0][1].x != 0 && set_C1[1][0].x != 0)
			strcpy(results, "A wins");
			
		else if(over && !next && set_C2[0][0].x != 0 && set_C2[1][1].x != 0)
			strcpy(results, "B wins");
		else if(over && !next && set_C2[0][1].x != 0 && set_C2[1][0].x != 0)
			strcpy(results, "B wins");
		
		else if(over)
			strcpy(results, "No win");
		
		if(!over)
			next = !next;
	
	}while(!over);
	
	
	displayGrid(set_F1, set_F2, over, indexRow, indexCol, next);
	printf("\n\n%s\n", results);
	
	for(int i=0; i<2; i++)
		for(int k=0; k<2; k++)
			printf("(%d,%d)\n", set_C1[i][k].x,set_C1[i][k].y);
			
	printf("\n");
			
	for(int i=0; i<2; i++)
		for(int k=0; k<2; k++)
			printf("(%d,%d)\n", set_C2[i][k].x,set_C2[i][k].y);
	
	return 0;
}


// function definitions

// solves for set F3
int
getSet_F3(cartesian set_F1[][F_COL], cartesian set_F2[][F_COL], cartesian set_F3[][F_COL])
{
	int i, j, nCardinality=0;
	
	// set F3 population
	for(i=0; i<F_ROW; i++)
		for(j=0; j<F_COL; j++)
		
			// assigns value to set F3 if the space is not taken by set F1 and F2
			// elements are stored according to their values:
			// x = row		y = col
			if(set_F1[i][j].x == 0 && set_F2[i][j].x == 0)
			{
				set_F3[i][j].x = i + 1;
				set_F3[i][j].y = j + 1;
				nCardinality++;
			}
			
			// assigns 0 to the variable if the position is already taken
			else
			{
				set_F3[i][j].x = 0;
				set_F3[i][j].y = 0;
			}
	
	return nCardinality;
}

// determines if over
Boolean
isOver(cartesian set_C1[][C_COL], cartesian set_C2[][C_COL],
	   cartesian set_F3[][F_COL], cartesian set_P[][P_COL], int nF3_Cardinality)
{
	Boolean bCon1 = FALSE,
			bCon2 = FALSE,
			bCon3 = FALSE;
			
	// evaluating (|F3| = 0)
	if(nF3_Cardinality == 0)
		bCon1 = TRUE;

	// evaluating second condition
	if(set_C1[0][0].x != 0 && set_C1[1][1].x != 0)
		bCon2 = TRUE;
	
	else if(set_C1[0][1].x != 0 && set_C1[1][0].x != 0)
		bCon2 = TRUE;
	
	// evaluating third condition
	if(set_C2[0][0].x != 0 && set_C2[1][1].x != 0)
		bCon3 = TRUE;
	
	else if(set_C2[0][1].x != 0 && set_C2[1][0].x != 0)
		bCon3 = TRUE;
	
	
	// evaluating (over)
	if(bCon1 || bCon2 || bCon3)
		return TRUE;
	
	return FALSE;
}

// adds an element to a set that is a subset of set F
void
addElement_F(cartesian * sElement, cartesian sSet[][F_COL])
{
	int xi = sElement->x -1;
	int yi = sElement->y -1;
	
	// elements are stored according to their values:
	// x = row		y = col	
	if(sSet[xi][yi].x == 0)
		sSet[xi][yi] = *sElement;
}

// adds an element to a set that is a subset of set C
void
addElement_C(cartesian * sElement, cartesian sSet[][C_COL])
{
	int xi = sElement->x -1;
	int yi = sElement->y -1;
	
	// elements are stored according to their values:
	// x = row		y = col
	if(sSet[xi][yi].x == 0)
		sSet[xi][yi] = *sElement;
}

// gets the cardinality of the (power set of F) intersection (set S)
int
getPatternsCompleted(cartesian sPowerSet[][F_COL])
{
	int nCardinality=0;
	
	// first element of set S
	if(sPowerSet[0][0].x != 0) // (1,1)
		if(sPowerSet[0][2].x != 0) // (1,3)
			if(sPowerSet[1][1].x != 0) // (2,2)
				if(sPowerSet[2][0].x != 0) // (3,1)
					if(sPowerSet[2][2].x != 0) // (3,3)
						nCardinality++;
	
	// second element		
	if(sPowerSet[3][3].x != 0) // (4,4)
		if(sPowerSet[3][5].x != 0) // (4,6)
			if(sPowerSet[4][4].x != 0) // (5,5)
				if(sPowerSet[5][3].x != 0) // (6,4)
					if(sPowerSet[5][5].x != 0) // (6,6)
						nCardinality++;					

	// third
	if(sPowerSet[0][4].x != 0) // (1,5)
		if(sPowerSet[1][3].x != 0) // (2,4)
			if(sPowerSet[1][4].x != 0) // (2,5)
				if(sPowerSet[1][5].x != 0) // (2,6)
					if(sPowerSet[2][4].x != 0) // (3,5)
						nCardinality++;	
	
	// 4th					
	if(sPowerSet[3][0].x != 0) // (1,1)
		if(sPowerSet[3][2].x != 0) // (1,3)
			if(sPowerSet[4][0].x != 0) // (2,2)
				if(sPowerSet[4][2].x != 0) // (3,1)
					if(sPowerSet[5][0].x != 0) // (3,3)
						if(sPowerSet[5][2].x != 0) // (5,2)
							nCardinality++;
	
	return nCardinality;
}

int
getCardinality_C(cartesian sSet[][C_COL])
{
	int i, k, nCardinality=0;
	
	// checks if the coordinate is not empty
	for(i=0; i<C_ROW; i++)
		for(k=0; k<C_COL; k++)
			if(sSet[i][k].x != 0)
				nCardinality++;
				
	return nCardinality;
}

// Function to display the grid
void displayGrid(cartesian set_F1[][F_COL], cartesian set_F2[][F_COL], Boolean over, int indexRow, int indexCol, int next) 
{
    system("cls"); // Clear the screen (Windows specific)
    int i, j;
    
    if(over)
    {
    	printf("GAME OVER\n");
	}
	else
	{
	    printf("WELCOME TO THE DSTRU OF DEATH GAME >:)\n");
	    printf("press WASD to navigate and press ENTER place your position\n");
	    if(next == 0)
	    printf("\nplayer 2 turn\n\n");
	    else if(next == 1)
	    printf("\nplayer 1 turn\n\n");
	}

    for (i = 0; i < F_ROW; i++) {
        for (j = 0; j < F_COL; j++) {
            if (i == indexRow && j == indexCol && !over)
                printf("\t|*|"); // Player position
            else if(set_F1[i][j].x != 0)
                printf("\t|A|"); // Box status
            else if(set_F2[i][j].x != 0)
                printf("\t|B|"); // Box status
            else
            	printf("\t|.|");
            
        }
        printf("\n\n");
    }
}

void
navigateGrid(cartesian set_F1[][F_COL], cartesian set_F2[][F_COL], Boolean over,
		     int *indexRow, int *indexCol, cartesian *pos, Boolean next)
{
	char input;
	
    // Display the initial gridd
    displayGrid(set_F1, set_F2, over, *indexRow, *indexCol, next);

    // loop
    do { 
        // Check if a key has been pressed
        if (kbhit()) {
            input = getch(); // Get the pressed key
            switch (input) 
            {
                case 'W':
                case 'w':
                    if (*indexRow > 0) 
                        (*indexRow)--;
                    break;
                case 'A':
                case 'a':
                    if (*indexCol > 0) 
                    (*indexCol)--;
                    break;
                case 'S':
                case 's':
                    if (*indexRow < F_ROW - 1) 
                        (*indexRow)++;
                    break;
                case 'D':
                case 'd':
                    if (*indexCol < F_COL - 1) 
                    (*indexCol)++;
                    break;

                case '\r': // Enter key
                    if (set_F1[*indexRow][*indexCol].x == 0 && set_F2[*indexRow][*indexCol].x == 0) 
                    {
                    	pos->x = *indexRow + 1;
                    	pos->y = *indexCol + 1;
                    	
                        if (next)
                        {
                        	set_F1[*indexRow][*indexCol].x = *indexRow+1; // Place player position
                        	set_F1[*indexRow][*indexCol].y = *indexCol+1;
                        }
                        else if(!next)
                        {
                        	set_F2[*indexRow][*indexCol].x = *indexRow+1; // Place player position
                        	set_F2[*indexRow][*indexCol].y = *indexCol+1;
                        }
                    }
                
                default:
                    break;
            }

            // Display the updated grid
            displayGrid(set_F1, set_F2, over, *indexRow, *indexCol, next);
            
        }
    }while (input != '\r');
}
