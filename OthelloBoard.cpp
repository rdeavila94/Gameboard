#include "OthelloBoard.h"
#include "OthelloMove.h"
#include "OthelloView.h"

using namespace std;


OthelloBoard::OthelloBoard(): GameBoard(), mPassCount(0), mBoard() {
	mBoard[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2 - 1] = WHITE;
	mBoard[BOARD_SIZE / 2][BOARD_SIZE / 2] = WHITE;
	mBoard[BOARD_SIZE / 2 - 1][BOARD_SIZE / 2] = BLACK;
	mBoard[BOARD_SIZE / 2][BOARD_SIZE / 2 - 1] = BLACK;
}

void OthelloBoard::ApplyMove(GameMove* MOVE) {
	OthelloMove* move = dynamic_cast<OthelloMove*>(MOVE);
	if (move->IsPass()) {
		mHistory.push_back(move);
		mNextPlayer = -mNextPlayer;
		mPassCount++;
		return;
	}
	mPassCount = 0;
	for (int r = -1; r <= 1; r++) {
		for (int c = -1, count = 0; c <= 1; c++) {
			int rCopy = move->mRow + r;
			int cCopy = move->mCol + c;
			bool b = 0;
			while (mBoard[rCopy][cCopy] == -mNextPlayer
				&& InBounds(rCopy, cCopy)) {
				count += 1;
				rCopy = rCopy + r;
				cCopy = cCopy + c;
				if (mBoard[rCopy][cCopy] == mNextPlayer && InBounds(rCopy, cCopy))
					b = !b;
			}
			if (b) {
				move->AddFlipSet(OthelloMove::FlipSet(count, c, r));
				for (count; count >= 0; count--) {
					rCopy = rCopy - r;
					cCopy = cCopy - c;
					mValue -= mBoard[rCopy][cCopy];
					mBoard[rCopy][cCopy] = mNextPlayer;
					mValue += mBoard[rCopy][cCopy];
				}//end for

			}//end if
			count = 0;
		}//end col for

	}
	mNextPlayer = -mNextPlayer;
	mHistory.push_back(move);
}

void OthelloBoard::GetPossibleMoves(vector<GameMove *> *list) const {
	for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++) {
		if (mBoard[0][i] == EMPTY) {
			for (int j = -1; j <= 1; j++) {
				for (int c = -1; c <= 1; c++) {
					int rCopy = (i / BOARD_SIZE) + j;
					int cCopy = (i % BOARD_SIZE) + c;
					while (mBoard[rCopy][cCopy] == -mNextPlayer &&
						InBounds(rCopy, cCopy)) {
						rCopy += j;
						cCopy += c;
						if (mBoard[rCopy][cCopy] == mNextPlayer &&
							InBounds(rCopy, cCopy)) {
							OthelloMove *m = dynamic_cast<OthelloMove *>(CreateMove());
							m->mRow = (i / BOARD_SIZE);
							m->mCol = (i % BOARD_SIZE);
							list->push_back(m);
							c = j = 2;
							break;
						}//end if
					}//end while
				}//end for
			}
		}//end traversal if
	}//end traversal for
	if (list->empty())
		list->push_back(new OthelloMove(-1, -1));

}//end method


void OthelloBoard::UndoLastMove() {
	int r = 0, c = 0;
	OthelloMove *last = dynamic_cast<OthelloMove*>(mHistory.back());
	if (last->IsPass()) {
		delete last;
		mHistory.pop_back();
		return;
	}
	mValue -= mBoard[last->mRow][last->mCol];
	mBoard[last->mRow][last->mCol] = EMPTY;
	for (OthelloMove::FlipSet& flips : last->mFlips) {
		r = last->mRow + flips.colDelta;
		c = last->mCol + flips.rowDelta;
		while (0 < flips.switched) {
			mBoard[r][c] = mNextPlayer;
			mValue += 2 * mNextPlayer;
			r += flips.colDelta;
			c += flips.rowDelta;
			flips.switched--;
		}
	}
	delete last;
	mNextPlayer = -mNextPlayer;
	mHistory.pop_back();
}