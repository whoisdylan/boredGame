// boredGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

class Board;
class Player;

enum direction {
	up, down, left, right
};

struct position {
	int row;
	int col;
};

class Board {
public:
	vector< vector <int> > gameBoard;
	void displayBoard();
	bool move(Player &player, direction direction);
};

class Player {
public:
	Player(position initPos) : pos(initPos) {}
	position pos;
	bool isAlive;
	direction getMove();
	bool attack();
};

Board *initBoard();
void initPlayers(vector<Player> &, int);
void playGame(Board &, vector<Player>, bool, int);

int _tmain(int argc, _TCHAR* argv[]) {
	cout << "hello, world" << endl;
	Board *board = initBoard();
	board->displayBoard();
	vector<Player> playerList;
	initPlayers(playerList, 2);
	for (vector<Player>::iterator iter = playerList.begin(); iter != playerList.end(); ++iter) {
		cout << "col = " << iter->pos.col << "row = " << iter->pos.row << endl;
	}
	playGame(*board, playerList, false, 0);
}

void initPlayers(vector<Player> &playerList, int numPlayers) {
	switch (numPlayers) {
	case 0:
		return;
		break;
	default:
		position playerPos = { 0, numPlayers-1 };
		Player newPlayer(playerPos);
		playerList.push_back(newPlayer);
		initPlayers(playerList,numPlayers - 1);
		break;
	}
}

direction Player::getMove() {
	char input;
	cin >> input;
	switch (input) {
	case 'w':
		return direction::up;
		break;
	case 'a':
		return direction::left;
		break;
	case 's':
		return direction::down;
		break;
	case 'd':
		return direction::right;
		break;
	default:
		cout << "Please enter w, a, s, or d" << endl;
		return this->getMove();
		break;
	}
}

Board *initBoard() {
	Board *board = new Board;
	board->gameBoard = vector< vector <int> >(8, vector<int>(8, 0));
	return board;
}

void Board::displayBoard() {
	for (vector< vector <int> >::iterator iter = this->gameBoard.begin(); iter != this->gameBoard.end(); ++iter) {
		for (vector<int>::iterator iter2 = iter->begin(); iter2 != iter->end(); ++iter2) {
			cout << *iter2;
		}
		cout << endl;
	}
}

bool checkMoveBounds(position pos, direction moveDir) {
	switch (moveDir) {
	case direction::up:
		if (pos.row > 0) {
			return true;
		}
		else {
			return false;
		}
		break;
	case direction::down:
		if (pos.row < 7) {
			return true;
		}
		else {
			return false;
		}
		break;
	case direction::left:
		if (pos.col > 0) {
			return true;
		}
		else {
			return false;
		}
		break;
	case direction::right:
		if (pos.col < 7) {
			return true;
		}
		else {
			return false;
		}
		break;
	default:
		return false;
		break;
	}

}

bool Board::move(Player &player, direction moveDir) {
	if (checkMoveBounds(player.pos, moveDir)) {
		(this->gameBoard.at(player.pos.row)).at(player.pos.col) = 0;
		switch (moveDir) {
		case direction::up:
			player.pos = { player.pos.row - 1, player.pos.col };
			break;
		case direction::down:
			player.pos = { player.pos.row + 1, player.pos.col };
			break;
		case direction::left:
			player.pos = { player.pos.row, player.pos.col - 1 };
			break;
		case direction::right:
			player.pos = { player.pos.row, player.pos.col + 1 };
			break;
		}
		(this->gameBoard.at(player.pos.row)).at(player.pos.col) = 1;
		return true;
	}
	else {
		cout << "Can't move in that direction" << endl;
		return false;
	}
}

void playGame(Board &board, vector<Player> playerList, bool isGameOver, int playersTurn) {
	if (isGameOver) {
		cout << "Game over" << endl;
	}
	else {
		Player currPlayer = playerList.at(playersTurn);
		const direction playersMove = currPlayer.getMove();
		cout << "player " << playersTurn << " moved " << playersMove << endl;
		bool playerDidMove = board.move(currPlayer, playersMove);
		if (!playerDidMove) {
			playGame(board, playerList, false, playersTurn);
			return;
		}
		board.displayBoard();
		int nextPlayersTurn = playersTurn == 0 ? 1 : 0;
		playerList.at(playersTurn) = currPlayer;
		playGame(board, playerList, false, nextPlayersTurn);
	}
}