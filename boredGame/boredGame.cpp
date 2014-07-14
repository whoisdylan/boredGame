// boredGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

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

};

class Player {
public:
	Player(position initPos) : pos(initPos) {}
	position pos;
	bool isAlive;
	direction getMove();
	void move(direction direction);
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
		position playerPos = { 0, numPlayers };
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

void playGame(Board &board, vector<Player> playerList, bool isGameOver, int playersTurn) {
	if (isGameOver) {
		cout << "Game over" << endl;
	}
	else {
		Player currPlayer = playerList.at(playersTurn);
		const direction playersMove = currPlayer.getMove();
		cout << "player " << playersTurn << " moved " << playersMove << endl;
		int nextPlayersTurn = playersTurn == 0 ? 1 : 0;
		playGame(board, playerList, false, nextPlayersTurn);
	}
}