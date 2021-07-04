#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
using namespace std;

int board[9][9] = { {0,6,0,3,0,0,8,0,4},
					{5,3,7,0,9,0,0,0,0},
					{0,4,0,0,0,6,3,0,7},
					{0,9,0,0,5,1,2,3,8},
					{0,0,0,0,0,0,0,0,0},
					{7,1,3,6,2,0,0,4,0},
					{3,0,6,4,0,0,0,1,0},
					{0,0,0,0,6,0,5,2,3},
					{1,0,2,0,0,9,0,8,0} };


void PrintBoard() {
	puts(

		".dP'Y8 88   88 8888b.   dP'Yb  88  dP  dP'Yb      .dP'Y8  dP'Yb  88     Yb    dP 888888 88'Yb \n"
		"`Ybo.' 88   88  8I  Yb dP   Yb 88odP  dP   Yb     `Ybo.' dP   Yb 88      Yb  dP  88__   88__dP\n"
		"o.`Y8b Y8   8P  8I  dY Yb   dP 88'Yb  Yb   dP     o.`Y8b Yb   dP 88  .o   YbdP   88''   88'Yb\n"
		"8bodP' `YbodP' 8888Y'   YbodP  88  Yb  YbodP      8bodP'  YbodP  88ood8    YP    888888 88  Yb \n"

	);
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0 && i > 0) {
			cout<< "_________________________________" << endl <<endl;
		}
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 0 && j>0) {
				cout << " | ";
			}
			cout << "[" << board[i][j] << "]";
		}
		
		
			cout << endl;
		
	}
		

}




bool FindNext(int *row,int* col) {
	int i = 0, j = 0;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			if (board[i][j] == 0) {
				*row = i; *col = j;
				return false;
			}
		}
	}
	return true;
}

bool isValid(int row, int col,int num) {
	int i,j;
	for (i = 0; i < 9; i++) {
		if (board[row][i] == num)
			return false;
	}
	for (i = 0; i < 9; i++) {
		if (board[i][col] == num)
			return false;
	}
	int boxx = (row / 3)*3, boxy = (col/ 3)*3;
	for (i = boxx; i < boxx + 3; i++) {
		for (j = boxy; j < boxy + 3; j++) {
			if (board[i][j] == num)
				return false;
		}
	}
	return true;
}

void PrintWithSteps() {
	system("cls");
	PrintBoard();
	Sleep(1);
}


bool Solve(int UserInput) {
	
	int row, col;
	if (FindNext(&row, &col)) {
	
		
		return true;
	}

	for (int i = 1; i < 10; i++) {
		if (isValid(row, col, i)) {
			if (UserInput==1)
				PrintWithSteps();
			board[row][col] = i;
			if (Solve(UserInput)) {
				return true;
			}
			if (UserInput == 1)
				printf("ERROR FOUND Returning back");
			board[row][col] = 0;
		}
	}


	
	return false;
}


bool InputBoardFromFile() {
	ifstream sudoku;
	sudoku.open("Sudoko.txt");
	if (sudoku.is_open()==false) {
		cout << "ERROR FILE NOT FOUND";
		return false;
	}
	int i, j,num;
	char c;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {

			 sudoku >>c>> num>>c;
			 board[i][j] = num;
		}
	}

	sudoku.close();
	return true;
}

bool InputBoardFromConsole() {
	int i, j;
	cout << "Enter The Sudoku row after row with spaces between Numbers"<<endl;
	for (i = 0; i < 9; i++) {
		cout << "Enter Row No:" << i << endl;
		cin >> board[i][0] >> board[i][1] >> board[i][2] >> board[i][3] >> board[i][4] >> board[i][5] >> board[i][6] >> board[i][7] >> board[i][8];

	}
	return true;
}


void main() {
	puts(

		".dP'Y8 88   88 8888b.   dP'Yb  88  dP  dP'Yb      .dP'Y8  dP'Yb  88     Yb    dP 888888 88'Yb \n"
		"`Ybo.' 88   88  8I  Yb dP   Yb 88odP  dP   Yb     `Ybo.' dP   Yb 88      Yb  dP  88__   88__dP\n"
		"o.`Y8b Y8   8P  8I  dY Yb   dP 88'Yb  Yb   dP     o.`Y8b Yb   dP 88  .o   YbdP   88''   88'Yb\n"
		"8bodP' `YbodP' 8888Y'   YbodP  88  Yb  YbodP      8bodP'  YbodP  88ood8    YP    888888 88  Yb \n"

	);

	cout << "Chose Option" << endl
		<< "[1]- From Code" << endl << "[2]- From File" << endl << "[3]- Enter In Console"<<endl;
	int UserInput;
	cin >> UserInput;
	if (UserInput < 0 || UserInput>3) {
		system("CLS");
		main();
	}
	switch (UserInput) {
	case(1):
		break;
	case(2):
		InputBoardFromFile();
		cout << "Who you like To view Step By Step?" << endl << "[1]-Yes" << endl << "[Otherwise]-No" << endl;
		cin >> UserInput;
		break;
	case(3):
		system("CLS");
		InputBoardFromConsole();
		
		break;
	}
	clock_t start, end;
	start = clock();
	Solve(UserInput);
	end = clock();
	

	system("CLS");
	PrintBoard();
	cout <<"Finished in:" <<((double)(end - start)) / CLOCKS_PER_SEC <<" Seconds.";
	return;
}