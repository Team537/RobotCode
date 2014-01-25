#include "Header.h"
char board[2][2];
void dispscreen(void)
{
	system("cls");
	cout << board[0][0] << "|" << board[0][1] << "|" << board[0][2] << endl;
	cout << "-+-+-" << endl;
	cout << board[1][0] << "|" << board[1][1] << "|" << board[1][2] << endl;
	cout << "-+-+-" << endl;
	cout << board[2][0] << "|" << board[2][1] << "|" << board[2][2] << endl;
}
void main (void)
{
	int Player = 1;
	dispscreen();
	_getch();
}