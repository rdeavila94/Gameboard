#include "GameExceptions.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include "TicTacToeBoard.h"
#include "TicTacToeMove.h"
#include "TicTacToeView.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;


int main(int argc, char* argv[]) {
	// Initialization
	GameBoard* board; // the state of the game board
	GameView* v; // a View for outputting the board via operator<<
	string userInput; // a string to hold the user's command choice
	vector<GameMove *> possMoves; // a holder for possible moves
	string command, player1, player2;
	int num = 0, game = 0;//convenient variable that will be used here and there;
	while (1) {
		cout << "What game do you want to play? 1) Othello 2) Tic Tac Toe 3) Exit" << endl;
		while (!(game > 0 && game < 4))
			cin >> game;
		if (game == 3)
			break;
		else if (game == 2) {
			board = new TicTacToeBoard();
			v = new TicTacToeView(board);
			player1 = "X", player2 = "O";
		}
		else {
			board = new OthelloBoard();
			v = new OthelloView(board);
			player1 = "Black", player2 = "White";
		}


		// Main loop
		do {
			board->GetNextPlayer() == 1 ? cout
				<< player1 << "'s move" : cout << player2<< "'s move";
			cout << endl << *v;
			board->GetPossibleMoves(&possMoves);
			cout << "Possible moves:\n";
			for (GameMove* a : possMoves) {
				cout << (string)*a << " ";
			}
			bool loop = 1;

			while (loop) {
				cout << "\nEnter a command: ";
				getline(cin, command);
				GameMove *m = board->CreateMove();
				if (command.find("undo") == 0) {
					istringstream(command.substr(4, command.length() - 1)) >> num;
					if (num > board->GetMoveCount())
						num = board->GetMoveCount();
					for (int i = 0; i < num; i++) {
						board->UndoLastMove();
					}
					delete m;
					loop = 0;
				}

				else if (command.find("move") == 0) {
					num = board->GetMoveCount();
					try {
						*m = command.substr(5, command.length() - 1);
						for (GameMove* a : possMoves) {
							if (*a == *m) {
								board->ApplyMove(m);
								loop = 0;
								break;
							}
						}
					}
					catch (GameException &e) {
						cout << "Invalid move.";
					}

					if (num == board->GetMoveCount()) {//nothing was applied.
						delete m;
					}
				}

				else if (command.compare("showValue") == 0) {
					cout << board->GetValue() << endl;
					delete m;
				}

				else if (command.compare("showHistory") == 0) {
					const vector<GameMove *> *a = board->GetMoveHistory();
					vector <GameMove *>::const_reverse_iterator itr;
					itr = a->rbegin();
					int b = board->GetMoveCount();
					while (itr != a->rend()) {
						b % 2 == 0 ? cout << player2 : cout << player1;
						cout << (string)**itr << endl;
						b--;
						itr++;
					}
					delete m;
				}

				else if (command.compare("quit") == 0) {
					delete m;
					loop = 0;
				}
				else
					delete m;

				if (!loop) {
					for (GameMove *a : possMoves)
						delete a;
					possMoves.clear();
				}
			}
		} while (!board->IsFinished() && command.compare("quit") != 0);
		if (!board->GetValue())
			cout << "Tie!" << endl;
		else
			board->GetValue() > 0 ? cout << player1 << " wins!" <<endl:
			cout << player2 << " wins!" << endl;
		cout << *v;
		delete board;
		game = 0;
	}
}//88 lines