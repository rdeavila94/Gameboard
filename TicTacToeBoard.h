#ifndef __TicTacToeBoard_H
#define __TicTacToeBoard_H

#include "GameBoard.h"
#include "GameMove.h"
#include "TicTacToeMove.h"

const int BOARD_SIZE_t = 3;
const int TURNS_TO_WIN = 5;
class TicTacToeBoard : public GameBoard {

public:

	enum PLAYER { EMPTY = 0, X = 1, O = -1 };

	TicTacToeBoard();

	virtual void GetPossibleMoves(std::vector<GameMove *> *list) const;

	virtual void ApplyMove(GameMove *move);

	virtual void UndoLastMove();

	virtual GameMove *CreateMove() const { return new TicTacToeMove; }

	inline static bool InBounds(int row, int col) {
		return row >= 0 && row < BOARD_SIZE_t && col >= 0 && col < BOARD_SIZE_t;
	}

	virtual bool IsFinished() const;

	bool done = 0;
private:
	friend class TicTacToeView;



	char mBoard[BOARD_SIZE_t][BOARD_SIZE_t];
};
#endif