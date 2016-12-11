#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#define WHITE 7
#define BLUE 3
#define LBLUE 9
#define RED 4
#define GREEN 2
#define LGREEN 10
#define YELLOW 6

typedef struct	{
	char N_SHIP [25];
	int SIZE;
}	SHIP;

HANDLE wHnd;
HANDLE rHnd;

void SetColor(int ForgC);
int MENU (void);
void SHOW1 (int m_n1 [10][10], int m_n2 [10][10], int T);
void SHOW2 (int m_n1 [10][10], int m_n2 [10][10], int T);
void SHOW3 (int m_n1 [10][10], int m_n2 [10][10]);
int WATER (int m_n1 [10][10], int m_n2 [10][10], int A, int B, int C, int D, int E, int TURN);
int SHOT (int m_n1 [10][10], int m_n2 [10][10], int T, int i, int j);
void FILL_PVP (int m_n1 [10][10], int m_n2 [10][10]);												//PVP --> Player Vs Player
void FILL_PVC (int m_n1 [10][10], int m_n2 [10][10]);												//PVC --> Player Vs Cpu
void FILL_CVC (int m_n1 [10][10], int m_n2 [10][10]);												//CVC --> CPU vs CPU
void SINK (int m_n1 [10][10], int m_n2 [10][10], int T);
void GAME_PVP (int m_n1 [10][10],int m_n2 [10][10]);												
void GAME_PVC (int m_n1 [10][10],int m_n2 [10][10]);												
void GAME_CVC (int m_n1 [10][10],int m_n2 [10][10]);												

int main (int argc, char* argv[])	{
	int M_N1 [10][10], M_N2[10][10], turn = 0, flag = 0, M = 0, i, j;
	char D;
	
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    
    SetConsoleTitle("BATTLESHIPS by Zeby");
	
	SMALL_RECT windowSize = {0, 0, 100, 600};							//CONSOLE SIZE
	SetConsoleWindowInfo(wHnd, 1, &windowSize);
	while (flag == 0)	{
		for (i = 0; i < 10; i++)	{
			for (j = 0; j < 10; j++)	{
				M_N1 [i][j] = 0;
				M_N2 [i][j] = 0;
			}
		}
		M = MENU ();
		switch (M)	{
			case 1:
				FILL_PVP (M_N1, M_N2);
				GAME_PVP (M_N1, M_N2);
				break;

			case 2:
				FILL_PVC (M_N1, M_N2);
				GAME_PVC (M_N1, M_N2);
				break;

			case 3:
				FILL_CVC (M_N1, M_N2);
				GAME_CVC (M_N1, M_N2);
				break;
		}
		
		do
		{
			fflush (stdin);
			SetColor (WHITE);
			printf ("\n\n\t\tDo you want to play again? (Y/N): ");
			scanf ("%c", &D);
			tolower (D);
		} while ((D != 'y') && (D != 'n'));

		if (D == 'y')	{
			flag = 0;
		}	else	{
			flag = 1;
			exit (0);
		}
	}
	SetColor (WHITE);
	system ("pause");
}

void SetColor(int ForgC)	{													//FUNCTION TO SET COLOR IN CONSOLE

     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))	{
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }

     return;
}

int MENU (void)	{
	int D = 0;

	do
	{
		system ("cls");
		SetColor (BLUE);
		printf ("\n\n\t\t\tWelcome to Battlehips!\n\n");
		SetColor (RED);
		printf ("\n\nChoose an option:\n\t1) Player vs player.\n\t2) Player vs CPU.\n\t3) CPU vs CPU.");
		SetColor (WHITE);
		printf ("\n\nDecision: ");
		scanf ("%d", &D);
	} while ((D < 1) || (D > 3));

	return D;
}

//MOVEMENTS CHECK AND FILL THE BOARD
int WATER (int m_n1 [10][10], int m_n2 [10][10], int A, int B, int C, int D, int E, int TURN)	{
	int i = 0, flag = 0;
		if (((A == C) || (B == D)) && ((A - C == E) || (C - A == E) || (B - D == E) || (D - B == E)))	{	//CHECKS USER INPUT
			if ((A == C) && (B > D))	{				//CHECK DOWN
				if (TURN == 0)	{
					for (i = B; i > D; i--)	{
						if (m_n1 [i][A] == 0)	{
							flag++;
						} else {
							flag--;
						}
					}
					if (flag == E)	{						//FLAG HAS TO BE EQUAL TO E (SIZE OF SHIP) TO CHECK IF THE POSITION ISN'T TAKEN
						for (i = B; i > D; i--)	{
							m_n1 [i][A] = E;
						}
						return 1;
					} else {
						return 0;
					}
			}	else	{
					for (i = B; i > D; i--)	{
						if (m_n2 [i][A] == 0)	{
							flag++ ;
						} else {
							flag--;
						}
					}
					if (flag == E)	{
						for (i = B; i > D; i--)	{
							m_n2 [i][A] = E;
						}				
						return 1;
					} else {
						return 0;
					}							
				}
			} else if ((A == C) && (D > B))	{		//CHECK UP
				if (TURN == 0)	{
					for (i = B; i < D; i++)	{
						if (m_n1 [i][A] == 0)	{
							flag++;
						} else {
							flag--;
						}
					}
					if (flag == E)	{
						for (i = B; i < D; i++)	{
							m_n1 [i][A] = E;
						}
						return 1;
					} else {
						return 0;
					}
				}	else	{
					for (i = B; i < D; i++)	{
						if (m_n2 [i][A] == 0)	{
							flag++;
						} else {
							flag--;
						}
					}
					if (flag == E)	{
						for (i = B; i < D; i++)	{
							m_n2 [i][A] = E;
						}
						return 1;
					} else {
						return 0;
					}				
				}
			} else if ((A > C) && (B == D))	{		//CHECK LEFT
				if (TURN == 0)	{
					for (i = A; i > C; i--)	{
						if (m_n1 [B][i] == 0)	{
							flag++;
						}	else	{
							flag--;
						}
					}
					if (flag == E)	{
						for (i = A; i > C; i--)	{
							m_n1 [B][i] = E;
						}
						return 1;	
					}	else	{
						return 0;
					}
				}	else	{
					for (i = A; i > C; i--)	{
						if (m_n2 [B][i] == 0)	{
							flag++;
						}	else	{
							flag--;
						}
					}
					if (flag == E)	{
						for (i = A; i > C; i--)	{
							m_n2 [B][i] = E;
						}
						return 1;	
					}	else	{
						return 0;
					}								
				}
			} else if ((C > A) && (B == D))	{		//CHECK RIGHT
				if (TURN == 0)	{
					for (i = A; i < C; i++)	{
						if (m_n1 [B][i] == 0)	{
							flag++;
						}	else	{
							flag--;
						}
					}
					if (flag == E)	{
						for (i = A; i < C; i++)	{
							m_n1 [B][i] = E;
						}
						return 1;
					} else 	{
						return 0;
					}
				}	else	{
					for (i = A; i < C; i++)	{
						if (m_n2 [B][i] == 0)	{
							flag++;
						}	else	{
							flag--;
						}
					}
					if (flag == E)	{
						for (i = A; i < C; i++)	{
							m_n2 [B][i] = E;
						}
						return 1;
					} else 	{
						return 0;
					}				
				}
			}
		}	else	{
			return 0;
		}
}

int SHOT (int m_n1 [10][10], int m_n2 [10][10], int T, int i, int j)	{
	if (T % 2 == 0)	{
		if (((m_n2 [i][j] >= 2) && (m_n2 [i][j] <= 5)) || (m_n2 [i][j] == 0)) {
			if ((i >= 0) && (i <= 9) && (j >= 0) && (j <= 9))	{
				return 1;
			}
		}	else	{
			return 0;
		}
	}	else	{
		if (((m_n1 [i][j] >= 2) && (m_n1 [i][j] <= 5)) || (m_n1 [i][j] == 0))	{
			if ((i >= 0) && (i <= 9) && (j >= 0) && (j <= 9)){
				return 1;
			}
		}	else	{
			return 0;
		}
	}
}

void SHOW1 (int m_n1 [10][10], int m_n2 [10][10], int T)	{					//SHOW FILL
	int i, j;
	if (T == 0)	{
		SetColor(WHITE);
		printf ("Player %d.\nW = Water with hit || H = Hit || X = Sink.\n\n", T+1);
		printf ("\t");
		for (i = 0; i < 10; i++)	{
			printf ("%d\t", i+1);	
		}
		printf ("\n");
		for (i = 0; i < 10; i++)	{
			SetColor(WHITE);
			printf ("%d\t", i+1);
			for (j = 0; j < 10; j++)	{
				if (m_n1 [i][j] == 0)	{
					SetColor(LBLUE);
					printf ("*\t");
				}	else	{
					SetColor(GREEN);
					printf ("B\t");
				}
			}
			printf ("\n");
		}
		printf ("\n\n");
	}	else {
		SetColor(WHITE);
		printf ("Player %d.\nW = Water || H = Hit || X = Sink.\n\n", T+1);
		printf ("\t");
		for (i = 0; i < 10; i++)	{
			printf ("%d\t", i+1);	
		}
		printf ("\n");
		for (i = 0; i < 10; i++)	{
			SetColor(WHITE);
			printf ("%d\t", i+1);
			for (j = 0; j < 10; j++)	{
				if (m_n2 [i][j] == 0)	{
					SetColor(LBLUE);
					printf ("*\t");
				}	else	{
					SetColor(GREEN);
					printf ("B\t");
				}
			}
			printf ("\n");
		}
		printf ("\n\n");	
	}
}

void SHOW2 (int m_n1 [10][10], int m_n2 [10][10], int T)	{					//SHOW GAME
	int i, j;
	if ((T - 1) % 2 == 0)	{
		SetColor(LGREEN);
		printf ("Player 1.\t\t\t\t\t\t\t\tTurn: %d.\nW = Water || H = Hit || X = Sink.\n\nBoard of player 2.\n\n", T);
		SetColor(WHITE);
		printf ("\t");
		for (i = 0; i < 10; i++)	{
			printf ("%d\t", i+1);	
		}
		printf ("\n");
		for (i = 0; i < 10; i++)	{
			SetColor(WHITE);
			printf ("%d\t", i+1);
			for (j = 0; j < 10; j++)	{
				if ((m_n2 [i][j] >= -5) && (m_n2 [i][j] < -1))	{
					SetColor (YELLOW);
					printf ("H\t");
				}	else if (m_n2 [i][j] == 1)	{
					SetColor (BLUE);
					printf ("W\t");
				}	else if (m_n2 [i][j] == -10)	{
					SetColor (RED);
					printf ("X\t");
				}	else	{
					SetColor (LBLUE);
					printf ("*\t");
				}
				
			}
			printf ("\n");
		}
		printf ("\n\n");
	}	else {
		SetColor(LGREEN);
		printf ("Player 2.\t\t\t\t\t\t\t\tTurn: %d.\nW = Water || H = Hit || X = Sink.\n\nBoard of player 1.\n\n", T);
		SetColor(WHITE);
		printf ("\t");
		for (i = 0; i < 10; i++)	{
			printf ("%d\t", i+1);	
		}
		printf ("\n");
		for (i = 0; i < 10; i++)	{
			SetColor(WHITE);
			printf ("%d\t", i+1);
			for (j = 0; j < 10; j++)	{
				if ((m_n1 [i][j] >= -5) && (m_n1 [i][j] < -1))	{
					SetColor (YELLOW);
					printf ("H\t");
				}	else if (m_n1 [i][j] == 1)	{
					SetColor (BLUE);
					printf ("W\t");
				}	else if (m_n1 [i][j] == -10)	{
					SetColor (RED);
					printf ("X\t");
				}	else	{
					SetColor (LBLUE);
					printf ("*\t");
				}
			}
			printf ("\n");
		}
		printf ("\n\n");	
	}
}

void SHOW3 (int m_n1 [10][10], int m_n2 [10][10])	{
	int i, j;
	
	SetColor(LGREEN);
	printf ("Board of Player 1.\n\n");
	SetColor(WHITE);
	printf ("\t");
	for (i = 0; i < 10; i++)	{
		printf ("%d\t", i+1);	
	}
	printf ("\n");
	for (i = 0; i < 10; i++)	{
		SetColor(WHITE);
		printf ("%d\t", i+1);
		for (j = 0; j < 10; j++)	{
			if ((m_n2 [i][j] >= -5) && (m_n2 [i][j] < -1))	{
				SetColor (YELLOW);
				printf ("H\t");
			}	else if (m_n2 [i][j] == 1)	{
				SetColor (BLUE);
				printf ("W\t");
			}	else if (m_n2 [i][j] == -10)	{
				SetColor (RED);
				printf ("X\t");
			}	else	{
				SetColor (LBLUE);
				printf ("*\t");
			}
		
		}
		printf ("\n");
	}
	printf ("\n\n");

	SetColor(LGREEN);
	printf ("Board of Player 2.\n\n");
	SetColor(WHITE);
	printf ("\t");
	for (i = 0; i < 10; i++)	{
		printf ("%d\t", i+1);	
	}
	printf ("\n");
	for (i = 0; i < 10; i++)	{
		SetColor(WHITE);
		printf ("%d\t", i+1);
		for (j = 0; j < 10; j++)	{
			if ((m_n1 [i][j] >= -5) && (m_n1 [i][j] < -1))	{
				SetColor (YELLOW);
				printf ("H\t");
			}	else if (m_n1 [i][j] == 1)	{
				SetColor (BLUE);
				printf ("W\t");
			}	else if (m_n1 [i][j] == -10)	{
				SetColor (RED);
				printf ("X\t");
			}	else	{
				SetColor (LBLUE);
				printf ("*\t");
			}
		}
		printf ("\n");
	}
	printf ("\n\n");	
}


void FILL_PVP (int m_n1 [10][10], int m_n2 [10][10])	{
	int i, j, fill = 0, x1, x2, y1, y2, flag = 0;							//SHIPS SIZE.
	SHIP S[4];																//aircraft = 5, battleship = 4, cruiser = 3, submarine = 2;
	
	S[0].SIZE = 5;
	S[1].SIZE = 4;
	S[2].SIZE = 3;
	S[3].SIZE = 2;
	
	strcpy (S[0].N_SHIP, "Aircraft carrier");
	strcpy (S[1].N_SHIP, "Battleship");
	strcpy (S[2].N_SHIP, "Cruiser");
	strcpy (S[3].N_SHIP, "Submarine");	
	
	while (fill < 2)	{
		for (i = 0; i < 4; i++)	{
			do	{
				system ("cls");
				SHOW1 (m_n1, m_n2, fill);						
				SetColor(WHITE);
				printf ("%s (%d blocks)\n", S[i].N_SHIP, S[i].SIZE);
				printf ("\tInitial coordinate (L): ");
				scanf ("%d", &y1);
				y1--;
				printf ("\tInitial coordinate (C): ");
				scanf ("%d", &x1);
				x1--;
				printf ("\tEnd coordinate (L): ");
				scanf ("%d", &y2);
				y2--;
				printf ("\tEnd coordinate (C): ");
				scanf ("%d", &x2);
				x2--;
			}	while (WATER (m_n1, m_n2, x1, y1, x2, y2, S[i].SIZE, fill) == 0);
		}
		system ("cls");
		printf ("\t\tYour ships on the board are: \n\n");
		SHOW1 (m_n1, m_n2, fill);
		sleep (5);
		
		fill++;	
	}
	
}

void FILL_PVC (int m_n1 [10][10], int m_n2 [10][10])	{
	int rn, i, j, fill = 0, x1, x2, y1, y2, flag = 0;
	time_t t;
	SHIP S[4];
	
	S[0].SIZE = 5;
	S[1].SIZE = 4;
	S[2].SIZE = 3;
	S[3].SIZE = 2;
	
	strcpy (S[0].N_SHIP, "Aircraft carrier");
	strcpy (S[1].N_SHIP, "Battleship");
	strcpy (S[2].N_SHIP, "Cruiser");
	strcpy (S[3].N_SHIP, "Submarine");

	srand(time(NULL));

	while (fill < 2)	{
		for (i = 0; i < 4; i++)	{
			do	{
				if (fill == 0)	{
					system ("cls");
					SHOW1 (m_n1, m_n2, fill);						
					SetColor(WHITE);
					printf ("%s (%d blocks)\n", S[i].N_SHIP, S[i].SIZE);
					printf ("\tInitial coordinate (L): ");
					scanf ("%d", &y1);
					y1--;
					printf ("\tInitial coordinate (C): ");
					scanf ("%d", &x1);
					x1--;
					printf ("\tEnd coordinate (L): ");
					scanf ("%d", &y2);
					y2--;
					printf ("\tEnd coordinate (C): ");
					scanf ("%d", &x2);
					x2--;
				}	else if (fill == 1)	{
						do {
							rn = rand () % 10;
							if (rn < 10)	{
								y1 = rn;
							}
						} while (y1 + S[i].SIZE > 9);
						do {
							rn = rand () % 10;
							if (rn < 10)	{
								x1 = rn;
							}
						} while (x1 + S[i].SIZE > 9);
					do
					{
						rn = rand () % 4;
						if (rn == 0)	{
							y2 = y1 - S[i].SIZE;
							x2 = x1;
						}	else if (rn == 1)	{
							y2 = y1 + S[i].SIZE;
							x2 = x1;
						}	else if (rn == 2)	{
							x2 = x1 + S[i].SIZE;
							y2 = y1;
						}	else if (rn == 3)	{
							x2 = x1 - S[i].SIZE;
							y2 = y1;
						}
					} while (((x2 < 0) || (x2 > 9)) || ((y2 < 0) || (y2 > 9))) ;
				}
			}	while (WATER (m_n1, m_n2, x1, y1, x2, y2, S[i].SIZE, fill) == 0);
		}
		system ("cls");
		if (fill == 0)	{
			printf ("\t\tYour ships on the board are: \n\n");
			SHOW1 (m_n1, m_n2, fill);			
		}
		system ("cls");
		SetColor (RED);
		printf ("\n\n\n\n\t\t\tLoading...");
		sleep (3);
		
		fill++;	
	}
}

void FILL_CVC (int m_n1 [10][10], int m_n2 [10][10])	{
	int rn, i, j, fill = 0, x1, x2, y1, y2, flag = 0;
	time_t t;
	SHIP S[4];
	
	S[0].SIZE = 5;
	S[1].SIZE = 4;
	S[2].SIZE = 3;
	S[3].SIZE = 2;
	
	strcpy (S[0].N_SHIP, "Aircraft carrier");
	strcpy (S[1].N_SHIP, "Battleship");
	strcpy (S[2].N_SHIP, "Cruiser");
	strcpy (S[3].N_SHIP, "Submarine");

	srand(time(NULL));

	while (fill < 2)	{
		for (i = 0; i < 4; i++)	{
			do	{
				if (fill == 0)	{
					system ("cls");
					do 	{
						rn = rand () % 10;
						if (rn < 10)	{
							y1 = rn;
						}
					} while (y1 + S[i].SIZE > 9);

					do   {
						rn = rand () % 10;
						if (rn < 10)	{
							x1 = rn;
						}
					} while (x1 + S[i].SIZE > 9);
					
					do
					{
						rn = rand () % 4;
						if (rn == 0)	{
							y2 = y1 - S[i].SIZE;
							x2 = x1;
						}	else if (rn == 1)	{
							y2 = y1 + S[i].SIZE;
							x2 = x1;
						}	else if (rn == 2)	{
							x2 = x1 + S[i].SIZE;
							y2 = y1;
						}	else if (rn == 3)	{
							x2 = x1 - S[i].SIZE;
							y2 = y1;
						}
					} while (((x2 < 0) || (x2 > 9)) || ((y2 < 0) || (y2 > 9))) ;
				}	else if (fill == 1)	{
						do {
							rn = rand () % 10;
							if (rn < 10)	{
								y1 = rn;
							}
						} while (y1 + S[i].SIZE > 9);
						do {
							rn = rand () % 10;
							if (rn < 10)	{
								x1 = rn;
							}
						} while (x1 + S[i].SIZE > 9);
					do
					{
						rn = rand () % 4;
						if (rn == 0)	{
							y2 = y1 - S[i].SIZE;
							x2 = x1;
						}	else if (rn == 1)	{
							y2 = y1 + S[i].SIZE;
							x2 = x1;
						}	else if (rn == 2)	{
							x2 = x1 + S[i].SIZE;
							y2 = y1;
						}	else if (rn == 3)	{
							x2 = x1 - S[i].SIZE;
							y2 = y1;
						}
					} while (((x2 < 0) || (x2 > 9)) || ((y2 < 0) || (y2 > 9))) ;
				}
			}	while (WATER (m_n1, m_n2, x1, y1, x2, y2, S[i].SIZE, fill) == 0);
		}
	
		fill++;	
	}

	system ("cls");
	i = 0;
	printf ("\t\tBoard of CPU 1:\n\n");
	SHOW1 (m_n1, m_n2, i);
	sleep (4);
	i++;
	system ("cls");
	SetColor (WHITE);
	printf ("\t\tBoard of CPU 2:\n\n");
	SHOW1 (m_n1, m_n2, i);
	sleep (4);
}

void SINK (int m_n1 [10][10], int m_n2 [10][10], int T)	{								//CHECKS FOR SHIPS SINK.
	int i, j;

	if (T % 2 == 0)	{
		for (i = 0; i < 10; i++)	{
			for (j = 0; j < 10; j++)	{
				if ((m_n2 [i][j] == -5) && (m_n2 [i][j+1] == -5) && (m_n2 [i][j+2] == -5) && (m_n2 [i][j+3] == -5) && (m_n2 [i][j+4] == -5))	{
					m_n2 [i][j] = -10;
					m_n2 [i][j+1] = -10;
					m_n2 [i][j+2] = -10;
					m_n2 [i][j+3] = -10;
					m_n2 [i][j+4] = -10;
				}	else if ((m_n2 [i][j] == -5) && (m_n2 [i+1][j] == -5) && (m_n2 [i+2][j] == -5) && (m_n2 [i+3][j] == -5) && (m_n2 [i+4][j] == -5))	{
					m_n2 [i][j] = -10;
					m_n2 [i+1][j] = -10;
					m_n2 [i+2][j] = -10;
					m_n2 [i+3][j] = -10;
					m_n2 [i+4][j] = -10;				
				}

				if ((m_n2 [i][j] == -4) && (m_n2 [i][j+1] == -4) && (m_n2 [i][j+2] == -4) && (m_n2 [i][j+3] == -4))	{
					m_n2 [i][j] = -10;
					m_n2 [i][j+1] = -10;
					m_n2 [i][j+2] = -10;
					m_n2 [i][j+3] = -10;
				}	else if ((m_n2 [i][j] == -4) && (m_n2 [i+1][j] == -4) && (m_n2 [i+2][j] == -4) && (m_n2 [i+3][j] == -4))	{
					m_n2 [i][j] = -10;
					m_n2 [i+1][j] = -10;
					m_n2 [i+2][j] = -10;
					m_n2 [i+3][j] = -10;
				}

				if ((m_n2 [i][j] == -3) && (m_n2 [i][j+1] == -3) && (m_n2 [i][j+2] == -3))	{
					m_n2 [i][j] = -10;
					m_n2 [i][j+1] = -10;
					m_n2 [i][j+2] = -10;
				}	else if ((m_n2 [i][j] == -3) && (m_n2 [i+1][j] == -3) && (m_n2 [i+2][j] == -3))	{
					m_n2 [i][j] = -10;
					m_n2 [i+1][j] = -10;
					m_n2 [i+2][j] = -10;
				}

				if ((m_n2 [i][j] == -2) && (m_n2 [i][j+1] == -2))	{
					m_n2 [i][j] = -10;
					m_n2 [i][j+1] = -10;
				}	else if ((m_n2 [i][j] == -2) && (m_n2 [i+1][j] == -2))	{
					m_n2 [i][j] = -10;
					m_n2 [i+1][j] = -10;
				}
			}
		}
	}	else	{
		for (i = 0; i < 10; i++)	{
			for (j = 0; j < 10; j++)	{
				if ((m_n1 [i][j] == -5) && (m_n1 [i][j+1] == -5) && (m_n1 [i][j+2] == -5) && (m_n1 [i][j+3] == -5) && (m_n1 [i][j+4] == -5))	{
					m_n1 [i][j] = -10;
					m_n1 [i][j+1] = -10;
					m_n1 [i][j+2] = -10;
					m_n1 [i][j+3] = -10;
					m_n1 [i][j+4] = -10;
				}	else if ((m_n1 [i][j] == -5) && (m_n1 [i+1][j] == -5) && (m_n1[i+2][j] == -5) && (m_n1 [i+3][j] == -5) && (m_n1 [i+4][j] == -5))	{
					m_n1 [i][j] = -10;
					m_n1 [i+1][j] = -10;
					m_n1 [i+2][j] = -10;
					m_n1 [i+3][j] = -10;
					m_n1 [i+4][j] = -10;				
				}

				if ((m_n1 [i][j] == -4) && (m_n1 [i][j+1] == -4) && (m_n1 [i][j+2] == -4) && (m_n1 [i][j+3] == -4))	{
					m_n1 [i][j] = -10;
					m_n1 [i][j+1] = -10;
					m_n1 [i][j+2] = -10;
					m_n1 [i][j+3] = -10;
				}	else if ((m_n1 [i][j] == -4) && (m_n1 [i+1][j] == -4) && (m_n1 [i+2][j] == -4) && (m_n1 [i+3][j] == -4))	{
					m_n1 [i][j] = -10;
					m_n1 [i+1][j] = -10;
					m_n1 [i+2][j] = -10;
					m_n1 [i+3][j] = -10;
				}

				if ((m_n1 [i][j] == -3) && (m_n1 [i][j+1] == -3) && (m_n1 [i][j+2] == -3))	{
					m_n1 [i][j] = -10;
					m_n1 [i][j+1] = -10;
					m_n1 [i][j+2] = -10;
				}	else if ((m_n2 [i][j] == -3) && (m_n1 [i+1][j] == -3) && (m_n1 [i+2][j] == -3))	{
					m_n1 [i][j] = -10;
					m_n1 [i+1][j] = -10;
					m_n1 [i+2][j] = -10;
				}

				if ((m_n1 [i][j] == -2) && (m_n1 [i][j+1] == -2))	{
					m_n1 [i][j] = -10;
					m_n1 [i][j+1] = -10;
				}	else if ((m_n1 [i][j] == -2) && (m_n1 [i+1][j] == -2))	{
					m_n1 [i][j] = -10;
					m_n1 [i+1][j] = -10;
				}
			}
		}
	}
}

void GAME_PVP (int m_n1 [10][10],int m_n2 [10][10])	{
	int TURN = 0, y, x, PLAYER = 0, i = 0, j = 0, P1 = 0, P2 = 0;

	while (PLAYER == 0)	{
	
		do {
			system ("cls");
			SHOW2 (m_n1, m_n2, TURN+1);
			SetColor (WHITE);
			printf ("Time to shoot!\n");
			printf ("\tLine: ");
			scanf ("%d", &y);
			printf ("\tColumn: ");
			scanf ("%d", &x);

			if (((y > 1) || (y < 10)) && ((x > 1) || (x < 10)))	{
				y--;
				x--;
			}

		} while (SHOT (m_n1, m_n2, TURN, y, x) == 0);

		if (TURN % 2 == 0)	{
			if ((m_n2 [y][x] > 1) && (m_n2 [y][x] <= 5)) 	{
				P2--;
				m_n2 [y][x] *= -1;															//MULTIPLY POS WITH -1 FOR HITS
			}	else if (m_n2 [y][x] == 0)	{
				m_n2 [y][x] = 1;															//1 FOR WATER
			}
		}	else	{
			if ((m_n1 [y][x] > 1) && (m_n1 [y][x] <= 5)) 	{
				P1--;
				m_n1 [y][x] *= -1;
			}	else if (m_n1 [y][x] == 0)	{
				m_n1 [y][x] = 1;
			}			
		}

		if (P1 == -14)	{
			PLAYER = -1;
		}	else if	(P2 == -14)	{
			PLAYER = -2;
		}
		
		SINK (m_n1, m_n2, TURN);

		if (PLAYER == 0)	{
			system ("cls");
			SHOW2 (m_n1, m_n2, TURN+1);
			SetColor (YELLOW);
			printf ("\t\t\tCHECK YOUR SHOT\n\n");
			sleep (3);
			TURN ++;
		}
	}

	if ((PLAYER == -1) || (PLAYER == -2))	{
		system ("cls");
		SHOW3 (m_n1, m_n2);
		sleep (3);
	}

	if (PLAYER == -1)	{
		system ("cls");
		SetColor (YELLOW);
		printf ("\n\n\t\t Player 2 is the winner!\n");
		sleep (3);
	}	else if (PLAYER == -2)	{
		system ("cls");
		SetColor (YELLOW);
		printf ("\n\n\t\t Player 1 is the winner!\n");
		sleep (3);
	}
}

void GAME_PVC (int m_n1 [10][10], int m_n2 [10][10])	{
	int TURN = 0, y, x, PLAYER = 0, i = 0, j = 0, P1 = 0, P2 = 0, flag = 1;
	int flagM = -1, flagH = 0, xA, yA, xA1, yA1, U = 0, CH = 0, size;				
													//CH --> Allos the re-assign of the original positions
	while (PLAYER == 0)	{							//xA and yA pos from AI										//xA1 and yA1 original pos if there was a hit
		if (TURN % 2 == 0)	{
			do {
				system ("cls");
				SHOW2 (m_n1, m_n2, TURN+1);
				SetColor (WHITE);
				printf ("Time to shoot!\n");
				printf ("\tLine: ");
				scanf ("%d", &y);
				printf ("\tColumn: ");
				scanf ("%d", &x);

				if (((y > 1) || (y < 10)) && ((x > 1) || (x < 10)))	{
					y--;
					x--;
				}
			} while (SHOT (m_n1, m_n2, TURN, y, x) == 0);
		}	else	{
			U++;
			flag = 1;										//flag for 'do while', i'm fed up with that loop
			if (flagM == -1)	{							//flagM = -1 ---> No ship discovered
				do {
					system ("cls");
					SHOW2 (m_n1, m_n2, TURN+1);
					SetColor (WHITE);
					xA = rand () % 10;						//Search with parity
					yA = rand () % 10;
					if ((xA % 2 == 0) && (yA % 2 == 0))	{
						flag = 0;
					}
				} while ((flag == 1) && (SHOT (m_n1, m_n2, TURN, yA, xA) == 0));
			}	else {										
					system ("cls");
					SHOW2 (m_n1, m_n2, TURN+1);										
					SetColor (WHITE);
					if (CH == 0)	{
						xA = xA1;
						yA = yA1;
					}
				if (flagH == 0)	{							//flagH = 0 ---> Down
					if (SHOT (m_n1, m_n2, TURN, yA, xA++) == 1)	{									//If SHOT returns 0, the else statement will shot to the following position
						xA++;
					}	else if (SHOT (m_n1, m_n2, TURN, yA, xA--) == 1)	{
						xA--;
						flagH++;
					}	else if (SHOT (m_n1, m_n2, TURN, yA--, xA) == 1)	{
						yA--;
						flagH++;
					}	else if (SHOT (m_n1, m_n2, TURN, yA++, xA) == 1)	{
						yA++;
						flagH++;
					}
			}	else if (flagH == 1)	{					//flagH = 1 ---> Up
					if (SHOT (m_n1, m_n2, TURN, yA, xA--) == 1)	{
						xA--;
					}	else if (SHOT (m_n1, m_n2, TURN, yA--, xA) == 1)	{
						yA--;
						flagH++;
					}	else if (SHOT (m_n1, m_n2, TURN, yA++, xA) == 1)	{
						yA++;
						flagH++;
					}	else if (SHOT (m_n1, m_n2, TURN, yA, xA++) == 1)	{
						xA++;
						flagH = 0;
					}
			}	else if (flagH == 2)	{					//flagH = 2 ---> Left
					if (SHOT (m_n1, m_n2, TURN, yA--, xA) == 1)	{
						yA--;	
					}	else if (SHOT (m_n1, m_n2, TURN, yA++, xA) == 1)	{
						flagH++;
						yA++;
					}	else if (SHOT (m_n1, m_n2, TURN, yA, xA++) == 1)	{
						xA++;
						flagH = 0;
					}	else if (SHOT (m_n1, m_n2, TURN, yA, xA--) == 1)	{
						xA--;
						flagH++;
					}
			}	else if (flagH == 3)	{					//flagH = 3 ---> Right
					if (SHOT (m_n1, m_n2, TURN, yA++, xA) == 1)	{
						yA++;	
					}	else if (SHOT (m_n1, m_n2, TURN, yA, xA++) == 1)	{
						xA++;
						flagH = 0;
					}	else if (SHOT (m_n1, m_n2, TURN, yA, xA--) == 1)	{
						xA--;
						flagH++;
					}	else if (SHOT (m_n1, m_n2, TURN, yA--, xA) == 1)	{
						yA--;
						flagH++;
					}
				}
			}
		}

		if (TURN % 2 == 0)	{
			if ((m_n2 [y][x] >= 2) && (m_n2 [y][x] <= 5)) 	{
				P2--;
				m_n2 [y][x] *= -1;															//MULTIPLY POS WITH -1 FOR HITS
			}	else if (m_n2 [y][x] == 0)	{
				m_n2 [y][x] = 1;															//1 FOR WATER
			}
		}	else	{
			if ((m_n1 [yA][xA] >= 2) && (m_n1 [yA][xA] <= 5)) 	{
				P1--;													//Size is for controlling the ship which is shooting and if they are beside
				CH++;
				if (flagM == -1)	{
					flagM = 1;
					xA1 = xA;
					yA1 = yA;
					size = m_n1 [yA][xA];
				}
				if (m_n1 [yA][xA] != size)	{							//If it shoots another ship this will set the IA to focus on the fist ship shot
					flagH++;
				}
				m_n1 [yA][xA] *= -1;
			}	else if (m_n1 [yA][xA] == 0)	{
				m_n1 [yA][xA] = 1;
				flagH++;
				CH = 0;
				if (flagH == 4)	{
					flagH = 0;
				}
			}			
		}

		if (P1 == -14)	{
			PLAYER = -1;
		}	else if	(P2 == -14)	{
			PLAYER = -2;
		}
		
		SINK (m_n1, m_n2, TURN);

		if (m_n1 [yA][xA] == -10)	{
			flagM = -1;
			flagH = 0;
			CH = 0;
		}

		system ("cls");
		SHOW2 (m_n1, m_n2, TURN+1);
		SetColor (YELLOW);
		printf ("\t\t\tCHECK YOUR SHOT\n\n");
		if (TURN % 2 != 0)	{
			printf ("\tyA: %d\txA: %d\tLoop: :%d\tHit: %d\tMovement: %d", yA+1, xA+1, U, flagH, flagM);					//This print is for checking random numbers shots
		}
		SetColor (YELLOW);
		sleep (3);
		TURN ++;
	}

	if ((PLAYER == -1) || (PLAYER == -2))	{
		system ("cls");
		SHOW3 (m_n1, m_n2);
		sleep (3);
	}

	if (PLAYER == -1)	{
		system ("cls");
		SetColor (YELLOW);
		printf ("\n\n\t\t CPU is the winner!\n");
		sleep (3);
	}	else if (PLAYER == -2)	{
		system ("cls");
		SetColor (YELLOW);
		printf ("\n\n\t\t Player 1 is the winner!\n");
		sleep (3);
	}
}

void GAME_CVC (int m_n1 [10][10],int m_n2 [10][10])	{
	int TURN = 0, y, x, PLAYER = 0, flag = 0, i = 0, j = 0, P1 = 0, P2 = 0;
	int flagM1 = -1, flagH1 = 0, flagM2 = -1, flagH2 = 0, xA, yA, xB, yB, xA1, yA1, xB1, yB1;				

	while (PLAYER == 0)	{							//xA and yA pos from AI
		do {										//xA1 and yA1 original pos if there was a hit
			system ("cls");
			flag = -1;
			SHOW2 (m_n1, m_n2, TURN+1);
			SetColor (WHITE);
			if (TURN % 2 == 0)	{
				if (flagM2 == -1)	{							//flagM = -1 ---> No ship discovered
					xB = rand () % 10;
					yB = rand () % 10;					
				}	else if (flagM2 == 0)	{					//flagM = 0 ---> Down
					if (flagH2 > 0)	{
						yB++;
					}	else	{
						xB1 = xB;
						yB1 = yB;
						yB++;
					}
				}	else if (flagM2 == 1)	{					//flagM = 1 ---> Up
					if (flagH2 > 0)	{
						yB--;
					}	else	{
						yB = yB1;
						yB--;
					}
				}	else if (flagM2 == 2)	{					//flagM = 2 ---> Left
					if (flagH2 > 0)	{
						xB--;
					}	else	{
						xB = xB1;
						yB = yB1;
						xB--;
					}
				}	else if (flagM2 == 3)	{					//flagM = 3 ---> Right
					if (flagH2 > 0)	{
						xB++;
					}	else	{
						xB = xB1;
						yB = yB1;
						xB++;
					}
				}
			}	else	{
				if (flagM1 == -1)	{							//flagM = -1 ---> No ship discovered
					xA = rand () % 10;
					yA = rand () % 10;					
				}	else if (flagM1 == 0)	{					//flagM = 0 ---> Down
					if (flagH1 > 0)	{
						yA++;
					}	else	{
						xA1 = xA;
						yA1 = yA;
						yA++;
					}
				}	else if (flagM1 == 1)	{					//flagM = 1 ---> Up
					if (flagH1 > 0)	{
						yA--;
					}	else	{
						yA = yA1;
						yA--;
					}
				}	else if (flagM1 == 2)	{					//flagM = 2 ---> Left
					if (flagH1 > 0)	{
						xA--;
					}	else	{
						xA = xA1;
						yA = yA1;
						xA--;
					}
				}	else if (flagM1 == 3)	{					//flagM = 3 ---> Right
					if (flagH1 > 0)	{
						xA++;
					}	else	{
						xA = xA1;
						yA = yA1;
						xA++;
					}
				}

				sleep (3);
			}

			if (TURN % 2 == 0)	{										//CHECK FOR POSITIONS WITH SHOTS
				if (m_n2 [y][x] != 0)	{
					flag = 1;
				}
			}	else	{
				if (m_n1 [yA][xA] != 0)	{
					flag = 1;
				}
			}
		} while (flag == 1);

		if (TURN % 2 == 0)	{
			if ((m_n2 [yB][xB] > 1) && (m_n2 [yB][xB] <= 5)) 	{
				P2--;
				m_n2 [yB][xB] *= -1;
				if (flagM2 == -1)	{
					flagM2++;										//MULTIPLY POS WITH -1 FOR HITS	
				}
				flagH2++;
			}	else if (m_n2 [yB][xB] == 0)	{
				m_n2 [yB][xB] = 1;															//1 FOR WATER
				if (flagM2 != -1)	{
					flagM2++;
					if (flagM2 == 3)	{
						flagM2 = 0;
					}
				}
			}
		}	else	{
			if ((m_n1 [yA][xA] > 1) && (m_n1 [yA][xA] <= 5)) 	{
				P1--;
				m_n1 [yA][xA] *= -1;
				if (flagM1 == -1)	{
					flagM1++;
				}
				flagH1++;
			}	else if (m_n1 [yA][xA] == 0)	{
				m_n1 [yA][xA] = 1;
				if (flagM1 != -1)	{
					flagM1++;
					if (flagM1 == 3)	{
						flagM1 = 0;
					}
				}
			}			
		}

		if (P1 == -14)	{
			PLAYER = -1;
		}	else if	(P2 == -14)	{
			PLAYER = -2;
		}
		
		SINK (m_n1, m_n2, TURN);

		if (m_n2 [yA][xA] == -10)	{
			flagM1 = -1;
			flagH1 = 0;
		}

		if (m_n1 [yB][xB] == -10)	{
			flagM2 = -1;
			flagH2 = 0;
		}

		system ("cls");
		SHOW2 (m_n1, m_n2, TURN+1);
		SetColor (YELLOW);
		printf ("\t\t\tCHECK YOUR SHOT\n\n");
		sleep (3);
		TURN ++;
	}

	if ((PLAYER == -1) || (PLAYER == -2))	{
		system ("cls");
		SHOW3 (m_n1, m_n2);
		sleep (3);
	}

	if (PLAYER == -1)	{
		system ("cls");
		SetColor (YELLOW);
		printf ("\n\n\t\t CPU 2 is the winner!\n");
		sleep (3);
	}	else if (PLAYER == -2)	{
		system ("cls");
		SetColor (YELLOW);
		printf ("\n\n\t\t CPU 1 is the winner!\n");
		sleep (3);
	}
}

//Realizar función GAME_PVC.