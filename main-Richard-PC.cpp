#include "GameExceptions.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;


int main(int argc, char* argv[]) {
	// Initialization
	OthelloBoard board; // the state of the game board
	OthelloView v(&board); // a View for outputting the board via operator<<
	string userInput; // a string to hold the user's command choice
	vector<GameMove *> possMoves; // a holder for possible moves
	string command;
	int num = 0;//convenient variable that will be used here and there;



	// Main loop
	do {
		board.GetNextPlayer() == 1 ? cout
			<< "Black's move\n" : cout << "White's move\n";
		cout << v;
		board.GetPossibleMoves(&possMoves);
		cout << "Possible moves:\n";
		for (OthelloMove* a : possMoves) {
			if (a->IsPass())
				cout << "pass";
			else
				cout << (string)*a << " ";
		}
		bool loop = 1;

		while (loop) {
			OthelloMove *m = board.CreateMove();
			cout << "\nEnter a command: ";
			getline(cin, command);
			if (command.find("undo") == 0) {
				istringstream(command.substr(4, command.length() - 1)) >> num;
				if (num > board.GetMoveCount())
					num = board.GetMoveCount();
				for (int i = 0; i < num; i++) {
					board.UndoLastMove();
				}
				delete m;
				loop = 0;
			}

			else if (command.find("move") == 0) {
				num = board.GetMoveCount();
				try {
					*m = command.substr(5, command.length() - 1);
					for (OthelloMove* a : possMoves) {
						if (*a == *m) {
							board.ApplyMove(m);
							loop = 0;
							break;
						}
					}
				}
				catch (OthelloException &e) {
					cout << "Invalid move.";
				}

				if (num == board.GetMoveCount()) {//nothing was applied.
					delete m;
				}
			}

			else if (command.compare("showValue") == 0) {
				cout << board.GetValue() << endl;
				delete m;
			}

			else if (command.compare("showHistory") == 0) {
				const vector<OthelloMove *> *a = board.GetMoveHistory();
				vector <OthelloMove *>::const_reverse_iterator itr;
				itr = a->rbegin();
				int b = board.GetMoveCount();
				while (itr != a->rend()) {
					b % 2 == 0 ? cout << "White:" : cout << "Black:";
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
				for (OthelloMove *a : possMoves)
					delete a;
				possMoves.clear();
			}
		}
	} while (!board.IsFinished() && command.compare("quit") != 0);
	for (OthelloMove* a : *board.GetMoveHistory())
		delete a;

	if (!board.GetValue())
		cout << "Tie";
	else
		board.GetValue() > 0 ? cout << "The winner is Black." :
		cout << "The winner is White";
}