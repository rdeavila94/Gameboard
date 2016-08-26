#include "OthelloMove.h"
#include "OthelloBoard.h"
#include <sstream>
#include <string>

using namespace std;

int OthelloMove::mOnHeap = 0;

OthelloMove::OthelloMove() :mRow(-1), mCol(-1) {};

OthelloMove::OthelloMove(int row, int col) : mRow(row), mCol(col) {};

GameMove& OthelloMove:: operator=(const std::string& a) {
	if (a == "pass") {
		mRow, mCol = -1;
		return *this;
	}
	istringstream h(a);
	char junk;
	h >> junk >> mRow >> junk >> mCol;
	if (!OthelloBoard::InBounds(mRow, mCol)) {
		throw OthelloException("Out of bounds");
	}
	return *this;
}

bool OthelloMove::Equals(const GameMove& other) const {
	const OthelloMove *m = dynamic_cast< const OthelloMove *>(&other);
	return (mCol == m->mCol && mRow == m->mRow);
}

OthelloMove::operator std::string() const {
	string str = "(" + to_string(mRow) + "," + to_string(mCol) + ")";
	if (mRow == -1 && mCol == -1)
		str = "pass";
	return str;
}