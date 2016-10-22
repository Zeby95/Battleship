#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <unistd.h>

typedef struct	{
	char N_SHIP [25];
	int SIZE;
}	SHIP;

HANDLE wHnd;
HANDLE rHnd;

void SHOW1 (int m_n1 [10][10], int m_n2 [10][10], int T);
void SHOW2 (int m_n1 [10][10], int m_n2 [10][10], int T);
int WATER (int m_n1 [10][10], int m_n2 [10][10], int m_nshoot1 [5][4], int m_nshoot2 [5][4], int A, int B, int C, int D, int E, int TURN);
void FILL (int m_n1 [10][10], int m_n2 [10][10], int m_nshoot1 [5][4], int m_nshoot2 [5][4]);
int CHECK (int m_n1 [10][10],int m_n2 [10][10]);
void GAME (int m_n1 [10][10],int m_n2 [10][10], int m_nshoot1 [5][4], int m_nshoot2 [5][4]);

int main (int argc, char* argv[])	{
	int M_N1 [10][10] = {{0}}, M_N2[10][10] = {{0}}, M_NSHOOT1 [5][4] = {{0}}, M_NSHOOT2 [5][4] = {{0}}, turn = 0, flag = 0;
	char D;
	
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    
    SetConsoleTitle("SEBA SEBA SEBA SEBA");
	
	SMALL_RECT windowSize = {0, 0, 100, 600};							//CONSOLE SIZE
	SetConsoleWindowInfo(wHnd, 1, &windowSize);
	while (flag == 0)	{
		FILL (M_N1, M_N2, M_NSHOOT1, M_NSHOOT2);
		GAME (M_N1, M_N2, M_NSHOOT1, M_NSHOOT2);
		do
		{
			printf ("\n\n\t\tWant yo play again? (Y/N): ");
			scanf ("%c", &D);
			tolower (D);
		} while ((D != 'y') || (D != 'n'));

		if (D == 'y')	{
			flag = 0;
		}	else	{
			flag = 1;
			exit (0);
		}
	}
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

//MOVEMENTS CHECK AND FILL THE BOARD
int WATER (int m_n1 [10][10], int m_n2 [10][10], int m_nshoot1 [5][4], int m_nshoot2 [5][4], int A, int B, int C, int D, int E, int TURN)	{
	int i = 0, flag = 0;
		if ((A == C) && (B < D) && (D - B == E))	{				//CHECK DOWN
			if (TURN == 0)	{
				for (i = B; i < D; i++)	{
					if (m_n1 [i][A] == 0)	{
						flag++;
					} else {
						flag--;
					}
				}
				if (flag == E)	{						//FLAG HAS TO BE EQUAL TO E (SIZE OF SHIP) TO CHECK IF THE POSITION ISN'T TAKEN
					for (i = B; i < D; i++)	{
						m_n1 [i][A] = E;
					}
					m_nshoot1 [E-2][0] = A;				//SAVE POSITIONS OF SHIPS
					m_nshoot1 [E-2][1] = B;
					m_nshoot1 [E-2][2] = C;
					m_nshoot1 [E-2][3] = D;
					return 1;
				} else {
					return 0;
				}
		}	else	{
				for (i = B; i < D; i++)	{
					if (m_n2 [i][A] == 0)	{
						flag++ ;
					} else {
						flag--;
					}
				}
				if (flag == E)	{
					for (i = B; i < D; i++)	{
						m_n2 [i][A] = E;
					}
					m_nshoot2 [E-2][0] = A;
					m_nshoot2 [E-2][1] = B;
					m_nshoot2 [E-2][2] = C;
					m_nshoot2 [E-2][3] = D;					
					return 1;
				} else {
					return 0;
				}							
			}
		} else if ((A == C) && (B > D) && (B - D == E))	{		//CHECK UP
			if (TURN == 0)	{
				for (i = B; i > D; i--)	{
					if (m_n1 [i][A] == 0)	{
						flag++;
					} else {
						flag--;
					}
				}
				if (flag == E)	{
					for (i = B; i > D; i--)	{
						m_n1 [i][A] = E;
					}
					m_nshoot1 [E-2][0] = A;
					m_nshoot1 [E-2][1] = B;
					m_nshoot1 [E-2][2] = C;
					m_nshoot1 [E-2][3] = D;
					return 1;
				} else {
					return 0;
				}
			}	else	{
				for (i = B; i > D; i--)	{
					if (m_n2 [i][A] == 0)	{
						flag++;
					} else {
						flag--;
					}
				}
				if (flag == E)	{
					for (i = B; i > D; i--)	{
						m_n2 [i][A] = E;
					}
					m_nshoot2 [E-2][0] = A;
					m_nshoot2 [E-2][1] = B;
					m_nshoot2 [E-2][2] = C;
					m_nshoot2 [E-2][3] = D;
					return 1;
				} else {
					return 0;
				}				
			}
		} else if ((A > C) && (B == D) && (A - C == E))	{		//CHECK LEFT
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
					m_nshoot1 [E-2][0] = A;
					m_nshoot1 [E-2][1] = B;
					m_nshoot1 [E-2][2] = C;
					m_nshoot1 [E-2][3] = D;
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
					m_nshoot2 [E-2][0] = A;
					m_nshoot2 [E-2][1] = B;
					m_nshoot2 [E-2][2] = C;
					m_nshoot2 [E-2][3] = D;
					return 1;	
				}	else	{
					return 0;
				}								
			}
		} else if ((A < C) && (B == D) && (C - A == E))	{		//CHECK RIGHT
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
					m_nshoot1 [E-2][0] = A;
					m_nshoot1 [E-2][1] = B;
					m_nshoot1 [E-2][2] = C;
					m_nshoot1 [E-2][3] = D;
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
					m_nshoot2 [E-2][0] = A;
					m_nshoot2 [E-2][1] = B;
					m_nshoot2 [E-2][2] = C;
					m_nshoot2 [E-2][3] = D;
					return 1;
				} else 	{
					return 0;
				}				
			}
		}
}

void SHOW1 (int m_n1 [10][10], int m_n2 [10][10], int T)	{					//SHOW FILL
	int i, j, GREEN = 2, BLUE = 9, WHITE = 7;
	if (T == 0)	{
		SetColor(WHITE);
		printf ("Player %d\n\n", T+1);
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
					SetColor(BLUE);
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
		printf ("Player %d\n\n", T+1);
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
					SetColor(BLUE);
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
	int i, j, RED = 4, YELLOW = 6, BLUE = 9, WHITE = 7, AQUA = 3, L_GREEN = 10;
	if ((T - 1) % 2 == 0)	{
		SetColor(L_GREEN);
		printf ("Player 1\t\t\t\t\t\t\t\tTurn: %d\n\n", T);
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
				if ((m_n1 [i][j] != 1) && (m_n1 [i][j] != -1)) 	{
					SetColor (BLUE);
					printf ("*\t");
				}	else if (m_n1 [i][j] == -1)	{
					SetColor (YELLOW);
					printf ("H\t");
				}	else if (m_n1 [i][j] == 1)	{
					SetColor (AQUA);
					printf ("W\t");
				}	else if (m_n1 [i][j] == -10)	{
					SetColor (RED);
					printf ("X\t");
				}
				
			}
			printf ("\n");
		}
		printf ("\n\n");
	}	else {
		SetColor(L_GREEN);
		printf ("Player 2\t\t\t\t\t\t\t\tTurn: %d\n\n", T);
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
				if ((m_n2 [i][j] != 1) && (m_n2 [i][j] != -1))	{
					SetColor (BLUE);
					printf ("*\t");
				}	else if (m_n2 [i][j] == -1)	{
					SetColor (YELLOW);
					printf ("H\t");
				}	else if (m_n2 [i][j] == 1)	{
					SetColor (AQUA);
					printf ("W\t");
				}	else if (m_n2 [i][j] == -10)	{
					SetColor (RED);
					printf ("X\t");
				}
			}
			printf ("\n");
		}
		printf ("\n\n");	
	}
}

void FILL (int m_n1 [10][10], int m_n2 [10][10], int m_nshoot1 [5][4], int m_nshoot2 [5][4])	{
	int i, j, BO, fill = 0, x1, x2, y1, y2, WHITE = 7, flag = 0;
	SHIP S[4];																 //aircraft = 5, battleship = 4, cruiser = 3, submarine = 2;
	
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
			}	while (WATER (m_n1, m_n2, m_nshoot1, m_nshoot2, x1, y1, x2, y2, S[i].SIZE, fill) == 0);
		}
		system ("cls");
		printf ("\t\tYour ships on the board are: \n\n");
		SHOW1 (m_n1, m_n2, fill);
		sleep (5);
		
		fill++;	
	}
	
}

void GAME (int m_n1 [10][10],int m_n2 [10][10], int m_nshoot1 [5][4], int m_nshoot2 [5][4])	{
	int TURN = 0, WHITE = 7, f, c, PLAYER = 0, flag = 0, i = 0, j = 0, P1 = 0, P2 = 0;

	while (PLAYER == 0)	{
		do {
			system ("cls");
			flag = 0;
			SHOW2 (m_n1, m_n2, TURN+1);
			SetColor (WHITE);
			printf ("Time to shoot!\n");
			printf ("\tLine: ");
			scanf ("%d", &f);
			f--;
			printf ("\tColumn: ");
			scanf ("%d", &c);
			c--;
			if (TURN % 2 == 0)	{
				if (m_n1 [f][c] == -1)	{
					flag == -1;
				}
			}	else	{
				if (m_n2 [f][c] == -1)	{
					flag == -1;
				}
			}
		} while ((f < 0) && (f > 10) && (c < 0) && (c > 10) && (flag == -1));

		if (TURN % 2 == 0)	{
			if ((m_n1 [f][c] != 0) && (m_n1 [f][c] != 1) && (m_n1 [f][c] != -1))	{
				P1--;
				m_n1 [f][c] *= -1;									//MULTIPLY POS WITH -1 FOR HITS
			}	else	{
				m_n1 [f][c] = 1;									//1 FOR WATER
			}
		}	else	{
			if ((m_n2 [f][c] != 0) && (m_n2 [f][c] != 1) && (m_n2 [f][c] != -1))	{
				P2--;
				m_n2 [f][c] *= -1;
			}	else	{
				m_n2 [f][c] = 1;
			}			
		}

		if (P1 == -54)	{
			PLAYER = -1;
		}	else if	(P2 == -54)	{
			PLAYER = -2;
		}
		
		if (PLAYER == 0)	{
			system ("cls");
			printf ("\t\t\tCHECK YOUR SHOT\n\n");
			SHOW2 (m_n1, m_n2, TURN+1);
			sleep (5);
			TURN ++;
		}
	}

	if (PLAYER == -1)	{
		system ("cls");
		printf ("\n\n\t\t Player 2 is the winner!\n");
		sleep (5);
	}	else if (PLAYER == -2)	{
		system ("cls");
		printf ("\n\n\t\t Player 1 is the winner!\n");
		sleep (5);
	}
}
//RELLENO FAIL. VERIFICAR
