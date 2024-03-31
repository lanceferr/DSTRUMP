/**********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
<Ronnie M. Abiog Jr.>, DLSU ID# <12341886>
<Lance Jacob T. Ferrer>, DLSU ID# <12344796>
<Owen Phillip C. San Luis>, DLSU ID# <12325562>
***********************************************************************************************************/

/*
 Authors: 	<Ronnie M. Abiog Jr.>, DLSU ID# <12341886>
			<Lance Jacob T. Ferrer>, DLSU ID# <12344796>
			<Owen Phillip C. San Luis>, DLSU ID# <12325562>

 Last Modified: March 31, 2024

 Version: 1.08
 
*/
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

typedef int Boolean; // either TRUE or FALSE

struct cartesianTag
{
	// (x, y) 	x for row		y for column
	int x;
	int y;
};

typedef struct cartesianTag cartesian;


int getSet_F3(cartesian [][F_COL], cartesian [][F_COL], cartesian [][F_COL]);
Boolean isOver(cartesian [][C_COL], cartesian [][C_COL], cartesian [][F_COL], int);
void addElement_F(cartesian *, cartesian [][F_COL]);
void addElement_C(cartesian *, cartesian [][C_COL]);
int getPatternsCompleted(cartesian [][F_COL]);
int getCardinality_C(cartesian [][C_COL]);
void displayGrid(cartesian [][F_COL], cartesian [][F_COL], cartesian *, Boolean, Boolean, char []);
void navigateGrid(cartesian [][F_COL], cartesian [][F_COL], int, int *, int *, cartesian *, Boolean);


int
main()
{
	/*
		definition of sets P and S from MP specs for reference
		
		each element corresponds to a quadrant
		cartesian set_P[P_ROW][P_COL] = {{{1,1}, {2,2}},  {{1,2}, {2,1}}};
		
	
		each row corresponds to a pattern in one quadrant
		cartesian set_S[S_ROW][S_COL] = {{{1,1}, {1,3}, {2,2}, {3,1}, {3,3}},
										 {{4,4}, {4,6}, {5,5}, {6,4}, {6,6}},
										 {{1,5}, {2,4}, {2,5}, {2,6}, {3,5}},
										 {{4,1}, {4,3}, {5,1}, {5,3}, {6,1}, {6,3}}};
	*/
		
	// variable declarations
	
	/*
		set variables
		player A = 1
		player B = 2
		set_C 1-2 contains quadrants in which the pattern is completed by player A and B respectively
		set_F 1-2 contains the spaces occupied by player A and B respectively
		set_F3 contains the empty spaces
	*/
	cartesian set_C1[C_ROW][C_COL] = {0}, set_C2[C_ROW][C_COL] = {0};
	cartesian set_F1[F_ROW][F_COL] = {0}, set_F2[F_ROW][F_COL] = {0}, set_F3[F_ROW][F_COL] = {0};

	/*
		player position variables
		pos is the position entered by the player
		quad_pos is the quadrant where pos is (e.g. top-left <=> (1,1))
		temp_pos is the indicator where the player is currently in
	*/
	cartesian pos = {0}, quad_pos = {0}, temp_pos = {0};
	
	/*
		control variables
		good determines if a new space is occupied
		over determines if the game is over
		next determines which player is supposed to move
	*/
	Boolean good = FALSE;
	Boolean over = FALSE;
	Boolean next = FALSE;
	
	/*
		counter variables
		nF_PatternCompleted 1-2 is the number of patterns completed by the player
								checked manually
		nF3_Cardinality is the number of empty spaces in the grid
		
		nC_Cardinality 1-2 is the number of patterns completed by the player
						   checked by relying on set_C 1 or 2
	*/
	int nF1_PatternsCompleted;
	int nF2_PatternsCompleted;
	int nF3_Cardinality = getSet_F3(set_F1, set_F2, set_F3);
	
	int nC1_Cardinality;
	int nC2_Cardinality;
	
	/*
		character variables
		results indicates the winner of the game
		input contains the character entered by the player while navigating in the grid
	*/
	char results[7];
	char input;
	
	
	// game start
	do	
	{		
		// displays the initial grid
	    displayGrid(set_F1, set_F2, &temp_pos, over, next, results);
	
	    // loop
	    do
		{
	        input = getch(); // gets the pressed key
	           
	        // converts WASD to up, left, down, right
	        switch (input) 
	        {
	    		case 'W':
	        	case 'w':
	                if (temp_pos.x > 0) 
	                    temp_pos.x--;
	                break;
	            case 'A':
	            case 'a':
	            	if (temp_pos.y > 0) 
	                	temp_pos.y--;
	                break;
	        	case 'S':
	            case 's':
	                if (temp_pos.x < F_ROW - 1) 
	                    temp_pos.x++;
	                break;
	            case 'D':
	            case 'd':
	                if (temp_pos.y < F_COL - 1) 
	                    temp_pos.y++;
	                break;

	            case '\r': // enter key
						                
	                // gets the position entered by the player
	               	pos = temp_pos;
	                    
	                // checks if the space is occupied
	                if (set_F3[pos.x][pos.y].x != 0) 
	                {                   
	                    // tells the program that there is a new addition to the spaces occupied
						good = !good;
							
						// adds the space to the spaces occupied by player A or B
						if(next)
							addElement_F(&pos, set_F1);	
								
						else if(!next)
							addElement_F(&pos, set_F2);		
	                }
	        }
	
	        // displays the updated grid
	        displayGrid(set_F1, set_F2, &temp_pos, over, next, results);
	        
	    }while (input != '\r');
	    
	    // removes the enter key in input
		input = '\0';
		
		// if there is a new space occupied
		if(good)
		{
			// determines which quadrant the pos is in
			quad_pos.x = (pos.x)/3 ;
			quad_pos.y = (pos.y)/3 ;	
			
			// updates the empty spaces left
			nF3_Cardinality = getSet_F3(set_F1, set_F2, set_F3);
			
			// determines the actual number of patterns completed
			nF1_PatternsCompleted = getPatternsCompleted(set_F1);
			nF2_PatternsCompleted = getPatternsCompleted(set_F2);
			
			// determines the number of patterns completed that currently are stored in the set_C 1-2
			nC1_Cardinality = getCardinality_C(set_C1);
			nC2_Cardinality = getCardinality_C(set_C2);
			
			// determines if there is a new pattern completed, then adds it to set_C 1 or 2
			if(next && (nF1_PatternsCompleted > nC1_Cardinality))
				addElement_C(&quad_pos, set_C1);	
			else if(!next && (nF2_PatternsCompleted > nC2_Cardinality))
				addElement_C(&quad_pos, set_C2);
				
			// determines if the game is over
			over = isOver(set_C1, set_C2, set_F3, nF3_Cardinality);
		
			// resets the flag
			if(!over)
				good = !good;
		}
		
		// determines the winner if the game is over
		if(over)
		{
			// checks if player A won
			if(next && set_C1[0][0].x != 0 && set_C1[1][1].x != 0)
				strcpy(results, "A wins");
			else if(next && set_C1[0][1].x != 0 && set_C1[1][0].x != 0)
				strcpy(results, "A wins");
			
			// checks if player B won
			else if(!next && set_C2[0][0].x != 0 && set_C2[1][1].x != 0)
				strcpy(results, "B wins");
			else if(!next && set_C2[0][1].x != 0 && set_C2[1][0].x != 0)
				strcpy(results, "B wins");
			
			// game over due to no empty spaces left
			else
				strcpy(results, " Draw ");
		}
			
		// ends the turn of the current player
		else
			next = !next;
	
	}while(!over);
	
	// displays the final grid along with the game result
	displayGrid(set_F1, set_F2, &temp_pos, over, next, results);
	
	// prevents the user from accidentally exiting the program
	printf("\t\tPress 0 to exit the program\n\n\n");
	while(getch() != 48);
	
	return 0;
}


// function definitions

/*
	getSet_F3 - determines the which spaces are not taken by set_F 1-2
	
	returns the cardinality of set_F3
*/
int
getSet_F3(cartesian set_F1[][F_COL], cartesian set_F2[][F_COL], cartesian set_F3[][F_COL])
{
	int i, j, nCardinality=0;
	
	// set F3 population
	for(i=0; i<F_ROW; i++)
		for(j=0; j<F_COL; j++)
		
			// assigns value to set F3 if the space is not taken by set F1 and F2
			/* 
				elements are stored according to their values:
				x = row		y = col
			*/
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

/*
	isOver - determines if the game is over
	
	returns TRUE if the game is over
	returns FALSE otherwise
*/
Boolean
isOver(cartesian set_C1[][C_COL], cartesian set_C2[][C_COL],
	   cartesian set_F3[][F_COL], int nF3_Cardinality)
{
	Boolean bCon1 = FALSE,
			bCon2 = FALSE,
			bCon3 = FALSE;
			
	// checks if there are no more empty spaces left
	if(nF3_Cardinality == 0)
		bCon1 = TRUE;

	// checks if player A completed the top-left and bottom-right patterns
	if(set_C1[0][0].x != 0 && set_C1[1][1].x != 0)
		bCon2 = TRUE;
		
	// checks if player A completed the top-right and bottom-left patterns
	else if(set_C1[0][1].x != 0 && set_C1[1][0].x != 0)
		bCon2 = TRUE;
	
	// checks if player B completed the top-left and bottom-right patterns
	if(set_C2[0][0].x != 0 && set_C2[1][1].x != 0)
		bCon3 = TRUE;
	
	// checks if player B completed the top-right and bottom-left patterns	
	else if(set_C2[0][1].x != 0 && set_C2[1][0].x != 0)
		bCon3 = TRUE;
	
	// game is over if at least one of the conditions is true
	if(bCon1 || bCon2 || bCon3)
		return TRUE;
	
	// game continues
	return FALSE;
}

/*
	addElement_F - adds a space to the spaces occupied by
				   the player
*/
void
addElement_F(cartesian * sElement, cartesian sSet[][F_COL])
{	
	// elements are stored according to their values:
	// cartesian x = row index + 1		cartesian y = col index + 1
	if(sSet[sElement->x][sElement->y].x == 0)
	{
		sSet[sElement->x][sElement->y].x = sElement->x + 1;
		sSet[sElement->x][sElement->y].y = sElement->y + 1;
		
	}
}

/*
	addElement_C - adds a quadrant to the quadrants in which
				   the pattern is completed by the player
*/
void
addElement_C(cartesian * sElement, cartesian sSet[][C_COL])
{
	// elements are stored according to their values:
	// cartesian x = row index + 1		cartesian y = col index + 1
	if(sSet[sElement->x][sElement->y].x == 0)
	{
		sSet[sElement->x][sElement->y].x = sElement->x + 1;
		sSet[sElement->x][sElement->y].y = sElement->y + 1;
		
	}
}

/*
	getPatternsCompleted - counts the patterns completed by a player
						   by checking the occupied spaces manually
	
	returns the count
*/
int
getPatternsCompleted(cartesian sPowerSet[][F_COL])
{
	int nCardinality=0;
	
	// first element of set_S
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

/*
	getCardinality_C - counts the number of completed patterns
					   by checking set_C 1 or 2
				       
	returns the count
*/
int
getCardinality_C(cartesian sSet[][C_COL])
{
	int i, k, nCardinality=0;
	
	// checks if the space is not empty
	for(i=0; i<C_ROW; i++)
		for(k=0; k<C_COL; k++)
			if(sSet[i][k].x != 0)
				nCardinality++;
				
	return nCardinality;
}

/*
	displayGrid - displays the current state of the grid, showing
				  the player position, occupied spaces, and empty
				  spaces
*/
void displayGrid(cartesian set_F1[][F_COL], cartesian set_F2[][F_COL],
			     cartesian *temp_pos, Boolean over, Boolean next, char results[]) 
{
    int i, k;
    
    // clear the screen
    system("cls");
    
    // if the game is not yet over
    if(!over)
	{
		// displays game header
		printf("\n\n\t\t\\vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv/\n");
		printf("\t\t>                                                                                   <\n");
		printf("\t\t>                                                                                   <\n");
	    printf("\t\t>                         WELCOME TO THE GAME OF TILES >:)                          <\n");
	    printf("\t\t>                                                                                   <\n");
	    printf("\t\t>                                                                                   <\n");
	    printf("\t\t/^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\\\n\n");
	    
	    // displays game instruction
	    printf("\t\tPress WASD to navigate and press ENTER to place your position\n");
	    printf("\t\t[ * ] - Current position\n");
	    printf("\t\t[ . ] - Empty space\n\n");
	    
	    // displays winning condition
	    printf("\t\t                                  WINNING CONDITION\n\n\n");
	    printf("\t\t             [X]        [ ]        [X]        [ ]        [O]        [ ]\n\n");
	    printf("\t\t             [ ]        [X]        [ ]        [O]        [O]        [O]\n\n");
	    printf("\t\t             [X]        [ ]        [X]        [ ]        [O]        [ ]\n\n");
	    printf("\t\t             [O]        [ ]        [O]        [X]        [ ]        [X]\n\n");
	    printf("\t\t             [O]        [ ]        [O]        [ ]        [X]        [ ]\n\n");
	    printf("\t\t             [O]        [ ]        [O]        [X]        [ ]        [X]\n\n");
	    printf("\t\tOccupy either all X or all O in the grid to win\n\n\n");
	    
	    // displays which player's turn it is
	    if(!next)
	   		printf("\t\tPlayer B's turn");
	    else
	    	printf("\t\tPlayer A's turn");
	}

	// displays the current state of the grid
    for (i=0; i<F_ROW; i++) 
	{
		printf("\n\n\n");
        for (k=0; k<F_COL; k++) 
		{
			// current position of the player
            if (i == temp_pos->x && k == temp_pos->y && !over)
                printf("\t\t[ * ]");
            
            // spaces occupied by player A
            else if(set_F1[i][k].x != 0)
                printf("\t\t[ A ]");
            
            // spaces occupied by player B
            else if(set_F2[i][k].x != 0)
                printf("\t\t[ B ]"); 
            
            // empty spaces
            else
            	printf("\t\t[ . ]");
        }
    }
	
	printf("\n\n\n");
	
	// if the game is over
    if(over)
    {
    	// display game over message above the final state of the grid
    	printf("\t\t\t\t\\vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv/\n");
    	printf("\t\t\t\t>                                                   <\n");
    	printf("\t\t\t\t>                      GAME OVER                    <\n");
    	printf("\t\t\t\t>                                                   <\n");
    	printf("\t\t\t\t>                       %s                      <\n", results);
    	printf("\t\t\t\t>                                                   <\n");
    	printf("\t\t\t\t/^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\\\n\n\n");
	}
}
