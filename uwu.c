
#include <stdio.h>

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
	// (x, y)
	int x;
	int y;
};

typedef struct cartesianTag cartesian;


// insert function prototypes

int getSet_F3(cartesian [][F_COL], cartesian [][F_COL], cartesian [][F_COL]);
Boolean isOver(cartesian [][C_COL], cartesian [][C_COL], cartesian [][F_COL], cartesian [][P_COL], int);
void addElement_F(cartesian *, cartesian [][F_COL]);
void addElement_C(cartesian *, cartesian [][C_COL]);


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
	cartesian alt_pos = {0};
	
	// other variable declarations
	Boolean good = FALSE;
	Boolean over = FALSE;
	Boolean next = FALSE;

	
	
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
	
	
	addElement_F(&set_P[0][0], set_F1);
	addElement_F(&set_P[0][1], set_F1);
	
	addElement_F(&set_P[1][0], set_F2);
	addElement_F(&set_P[1][1], set_F2);

	
	
	getSet_F3(set_F1, set_F2, set_F3);
	
	printf("\n\nSet F3:\n");
	for(int i=0; i<F_ROW; i++)
	{
		for(int j=0; j<F_COL; j++)
//			printf("(%d, %d)\t", set_F3[i][j].x, set_F3[i][j].y);
			if(set_F3[i][j].x == 0)
				printf("0\t");
			else
				printf("1\t");
			
	printf("\n\n");
	}
	
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

	// evaluating ?x (x ? P(C1) ? |x| > 0 ? x ? P)
	if(set_C1[0][0].x != 0 && set_C1[1][1].x != 0)
		bCon2 = TRUE;
	
	else if(set_C1[0][1].x != 0 && set_C1[1][0].x != 0)
		bCon2 = TRUE;
	
	
	// evaluating ?x (x ? P(C2) ? |x| > 0 ? x ? P)
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

