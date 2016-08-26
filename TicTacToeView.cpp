#include "TicTacToeView.h"

using namespace std;

void TicTacToeView::PrintBoard(ostream& a) const {
	cout << "- 0 1 2";
	int newLine = 0, col = 0;
	for (char *pToBoard = &mTTTBoard->mBoard[0][0]; pToBoard != &mTTTBoard->mBoard[BOARD_SIZE_t][0];
		pToBoard++, newLine++) {
		if (newLine % 3 == 0)
			cout << endl << col++;
		if (*pToBoard == 1)
			cout << "X ";
		else if (*pToBoard == -1)
			cout << "O ";
		else
			cout << ". ";

	}
	cout << endl;
}