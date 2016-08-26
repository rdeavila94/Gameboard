#ifndef __TicTacToeView_H
#define __TicTacToeView_H
#include "GameView.h"
#include "TicTacToeBoard.h"
#include <iostream>

class TicTacToeView : public GameView {
private:
	TicTacToeBoard *mTTTBoard;
	virtual void PrintBoard(std::ostream &s) const;

public:
	TicTacToeView(GameBoard *b) : mTTTBoard(dynamic_cast<TicTacToeBoard*>(b)) {}
};
#endif