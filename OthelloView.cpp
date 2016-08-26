#include "OthelloView.h"

using namespace std;

void OthelloView::PrintBoard(ostream& a) const {
	cout << "- 0 1 2 3 4 5 6 7";
	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << endl << i << " ";
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (mOthelloBoard->mBoard[i][j] == 1)
				cout << "B ";
			else if (mOthelloBoard->mBoard[i][j] == -1)
				cout << "W ";
			else
				cout << ". ";
		}
	}
	cout << endl;
}