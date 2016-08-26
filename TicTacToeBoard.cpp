#include "TicTacToeBoard.h"

using namespace std;

TicTacToeBoard::TicTacToeBoard() : GameBoard(), mBoard() {}


void TicTacToeBoard::ApplyMove(GameMove *m) {
	TicTacToeMove* move = dynamic_cast<TicTacToeMove*>(m);
	mBoard[move->mRow][move->mCol] = mNextPlayer;
	mHistory.push_back(move);
	if (mHistory.size() >= TURNS_TO_WIN && mHistory.size()) {
		if (IsFinished()) {
			mValue = mNextPlayer;
		}
		else if (mHistory.size() == 9) {
			done = true;
		}
	}
	mNextPlayer = -mNextPlayer;
}

void TicTacToeBoard::GetPossibleMoves(vector<GameMove*> *list) const{
	for (int i = 0; i < BOARD_SIZE_t; i++) {
		for (int j = 0; j < BOARD_SIZE_t; j++)
		if (mBoard[i][j] == EMPTY) {
			TicTacToeMove *m = dynamic_cast<TicTacToeMove *>(CreateMove());
			m->mRow = i;
			m->mCol = j;
			list->push_back(m);
		}
	}
}

void TicTacToeBoard::UndoLastMove() {
	TicTacToeMove *last = dynamic_cast<TicTacToeMove*>(mHistory.back());
	mBoard[last->mRow][last->mCol] = EMPTY;
	mNextPlayer = -mNextPlayer;
	delete last;
	mHistory.pop_back();
}

bool TicTacToeBoard::IsFinished() const {
	if (done)
		return done;
	for (int i = 0; i < BOARD_SIZE_t; i++) {
		if (mBoard[i][0] == mBoard[i][1] && mBoard[i][1] == mBoard[i][2] && mBoard[i][0] != EMPTY
			&& mBoard[i][1] != EMPTY && mBoard[i][2] != EMPTY)
			return true;
	}
	for (int i = 0; i < BOARD_SIZE_t; i++) {
		if (mBoard[0][i] == mBoard[1][i] && mBoard[1][i] == mBoard[2][i] && mBoard[0][i] != EMPTY
			&& mBoard[1][i] != EMPTY && mBoard[2][i] != EMPTY)
			return true;
	}
	if (mBoard[0][0] == mBoard[1][1] && mBoard[1][1] == mBoard[2][2] && mBoard[0][0] != EMPTY
		&& mBoard[1][1] != EMPTY && mBoard[2][2] != EMPTY)
		return true;
	if (mBoard[0][2] == mBoard[1][1] && mBoard[1][1] == mBoard[2][0] && mBoard[0][2] != EMPTY
		&& mBoard[1][1] != EMPTY && mBoard[2][0] != EMPTY)
		return true;
	return false;
}