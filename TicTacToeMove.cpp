#include "TicTacToeMove.h"
#include "TicTacToeBoard.h"
#include <iostream>
#include <sstream>
using namespace std;

int TicTacToeMove::mOnHeap = 0;

TicTacToeMove::TicTacToeMove() :mRow(-1), mCol(-1) {}

TicTacToeMove::TicTacToeMove(int row, int col) : mRow(row), mCol(col) {}

GameMove& TicTacToeMove:: operator=(const std::string& a) {
	istringstream h(a);
	char junk;
	h >> junk >> mRow >> junk >> mCol;
	if (!(TicTacToeBoard::InBounds(mRow, mCol))) {
		throw GameException("Out of bounds");
	}
	return *this;
}

bool TicTacToeMove::Equals(const GameMove& other) const {
	const TicTacToeMove *m = dynamic_cast< const TicTacToeMove *>(&other);
	return (mCol == m->mCol && mRow == m->mRow);
}

TicTacToeMove::operator std::string() const {
	string str = "(" + to_string(mRow) + "," + to_string(mCol) + ")";
	return str;
}