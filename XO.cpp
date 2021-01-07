#include "XO.hpp"
#include "Deque.hpp"
#include <vector>

// Default Constructor 
XO::XO() {
	
}

//Parameterized Constructor - Makes certain number of moves
XO::XO(const int8_t* play, const uint8_t* pos, const uint8_t& n) {
	
	//int count = 0;
	if (!makeMoves(play, pos, n)) // if makeMoves returns false an error is thrown 
	{
		//count = b.numMoves;
		throw std::logic_error("Invalid move!");
	}
}

void XO::show() {
	std::cout << b; // Show the board
}

// Make move calls the private method makeMove to make a certain move and update the private variables
bool XO::makeMove(const int8_t& play, const uint8_t& pos) {
	bool flag = false; // flag is set to false 
	 // Check if the move is valid
	if ((b.numMoves < 9 && b.state[pos] == 0) && (play == -1 || play == 1) && (b.turn[b.numMoves -1] != play) && pos < 9 && !gameOver() && pos >= 0) {
		/*b.turn[b.numMoves] = play;
		b.moves[b.numMoves] = pos;
		b.state[pos] = play;
		b.numMoves = b.numMoves + 1;*/
		makeMove(play, pos, b); // call makeMove
		flag = true; // flag is set to true 
	}
	else {
		flag = false;
	}
	return flag; // return flag
}

// MakeMoves similar to the parameterized cntructor only does not throw an error returns a boolean value 
bool XO::makeMoves(const int8_t* play, const uint8_t* pos, const uint8_t& n) {

	bool flag = false;
	int8_t ostate[9];
	uint8_t omoves[9];
	int8_t oturn[9];
	uint8_t onumMoves = b.numMoves;
	for (int i = 0; i < 9; i++) {
		ostate[i] = b.state[i];
		omoves[i] = b.moves[i];
		oturn[i] = b.turn[i];
	}
	if (n + b.numMoves <= 9 && n > 0) {
		for (int i = 0; i < n; i++) {
			flag = makeMove(play[i], pos[i]);
			if (!flag) {
				for (int i = 0; i < 9; i++) {
					b.state[i] = ostate[i];
					b.moves[i] = omoves[i];
					b.turn[i] = oturn[i];
					b.numMoves = onumMoves;
				}
				return flag;
			}
		}
		return flag;
	}
	else {
		return flag;
	}
	
	
}

bool XO::makeOptimalMove() {
	if (gameOver())//b.numMoves < 1)
	{
		return false;
	}

	Deque<BoardXO> q;
	struct board
	{
		int child; // score of the child of the given node
		
		uint32_t node; // ID of the parent
		BoardXO currState; //current state 
		bool visited; //To check if the given board has been visited or not 

		
	};

	
	std::vector <board> tree; // A vector to hold the tree
	board brd;
	brd.visited = false; // the board has not been visited
	brd.currState = b; // current state of the board
	tree.push_back(brd); // push the given board to the vector 

	int IDcounter = 0; // Id counter initialized to 0
	int nextPlayer = 0;
	int player = b.turn[b.numMoves - 1] * -1; // the player we have to find the optimal move for 
	b.id = IDcounter; // The board is given an ID
	
	q.pushBack(b); //push the board to the deque

	//while deck is not empty
	while (!q.isEmpty())
	{
		BoardXO game = q.front();//get the board in the front of the deque
		q.popFront(); // pop the front of the deque
		int8_t nTurn = game.turn[game.numMoves - 1]; // Finidng the player who played last

		if (!gameOver(game)) //If the game is not in the terminal state i.e game is not over
		{
			for (int i =  0; i < 9; i++) // for all the moved
			{
				if (game.state[i] == 0) // if the game stae for that move is 0
				{
					IDcounter++; 
					BoardXO temp = game; //holfing the temporary state of the game
					temp.id = IDcounter;
					if (nTurn == -1) //if the player who last played is X then the next player is O
					{
						nextPlayer = 1;
					}
					else //and vice versa
					{
						nextPlayer = -1;
					}
					makeMove(nextPlayer, i, temp); //make the move if possible
					board temp1;
					temp1.visited = false;
					temp1.currState = temp;
					temp1.node = game.id;
					tree.push_back(temp1);
					q.pushBack(temp);
				}
			}

		}
		else // If the game is in the terminal state score the game 
		{

			if (winner(game) == player) // If the player who won the game is the player we are finding the optimal move for
			{
				tree[game.id].child = 10 - game.numMoves; // maximize the score of the board
			}
			else if (winner(game) == 0) // case for draw
			{
				tree[game.id].child = 0;
			}
			else // if the opponent wins then minimize the score of the board
			{
				tree[game.id].child =   game.numMoves - 10;
			}
		}
	}
	int optimalBoard = 1; 
	for (int i = (tree.size() - 1); i > 0; i--) // Starting from the right ost node
	{
		int parent = tree[i].node; //get the parent of the board 
		int8_t previousPlayer = tree[i].currState.turn[tree[i].currState.numMoves - 1];
		if (previousPlayer == player) //If the previous player is the player we are finding the optimal move for 
		{
			if ((tree[i].child > tree[parent].child) || (!tree[parent].visited)) // find the maximum score if the given state has not been visited
			{
				optimalBoard = i;
				tree[parent].child = tree[i].child;
				tree[parent].visited = true; // Update the visited board
				
			}
		}
		else // minimize the score of the opponent 
		{
			if ((tree[i].child < tree[parent].child) || (!tree[parent].visited))
			{
				tree[parent].child = tree[i].child;
				tree[parent].visited = true;
			}
		}

	}
	b = tree[optimalBoard].currState; // update the board b
	return true;
	
}

BoardXO XO::getBoard() {
	return b; // return the move 
}

bool XO::gameOver() {
	return gameOver(b);
	/*
	bool flag = false;
	if (b.numMoves == 9 || (winner() == 1 || winner() == -1)) {
		flag = true;
	}
	else {
		flag = false;
	}
	return flag;
	*/
}

int8_t XO::winner() {
	return winner(b);
	/*
	// check all the rows 
	for (int i = 0; i < 3; i++) {
		if (b.state[3 * i] == b.state[(3 * i) + 1] && b.state[(3 * i) + 1] == b.state[(3 * i) + 2]) {
			if (b.state[3 * i] == -1) {
				return -1;
			}
			else if (b.state[3 * i] == 1) {
				return 1;
			}
		}
	}
	//check all the columns 
	for (int i = 0; i < 3; i++) {
		if (b.state[i%3] == b.state[(i % 3) + 3] && b.state[(i % 3) + 3] == b.state[(i % 3) + 6]) {
			if (b.state[(i % 3)] == -1) {
				return -1;
			}
			else if (b.state[(i % 3)] == 1) {
				return 1;
			}
		}
	}
	
	//check the diagonals 
	if (b.state[0] == b.state[4] && b.state[4] == b.state[8]) {
		if (b.state[0] == -1) {
			return -1;
		}
		else if (b.state[0] == 1) {
			return 1;
		}
	}
	if (b.state[2] == b.state[4] && b.state[4] == b.state[6]) {
		if (b.state[2] == -1) {
			return -1;
		}
		else if (b.state[2] == 1) {
			return 1;
		}
	}

	return 0;
	*/
}

// To check if the game is over 
bool XO::gameOver(const BoardXO& brd)
{
	bool flag = false; // set flag to false  
	// check if the game os over given the conditions
	if (brd.numMoves == 9 || (winner(brd) == 1 || winner(brd) == -1)) {
		flag = true;
	}
	else {
		flag = false;
	}
	return flag; // return flage

} 
int8_t XO::winner(const BoardXO& brd)
{

	// check all the rows 
	for (int i = 0; i < 3; i++) {
		if (brd.state[3 * i] == brd.state[(3 * i) + 1] && brd.state[(3 * i) + 1] == brd.state[(3 * i) + 2]) {
			if (brd.state[3 * i] != 0) {
				return brd.state[3 * i]; // return the winner 
			}
			/*if (brd.state[3 * i] == -1) {
				return -1;
			}
			else if (brd.state[3 * i] == 1) {
				return 1;
			}*/
		}
	}
	//check all the columns 
	for (int i = 0; i < 3; i++) {
		if (brd.state[i % 3] == brd.state[(i % 3) + 3] && brd.state[(i % 3) + 3] == brd.state[(i % 3) + 6]) {
			if (brd.state[i%3] != 0) {
				return brd.state[i%3]; // return the winner 
			}
			//if (brd.state[(i % 3)] == -1) {
			//	return -1;
			//}
			//else if (brd.state[(i % 3)] == 1) {
			//	return 1;
			//}
		}
	}

	//check the diagonals 
	if (brd.state[0] == brd.state[4] && brd.state[4] == brd.state[8]) {
		if (brd.state[0] != 0) {
			return brd.state[0]; // return the winner 
		}
		//if (brd.state[0] == -1) {
		//	return -1;
		//}
		//else if (brd.state[0] == 1) {
		//	return 1;
		//}
	}
	if (brd.state[2] == brd.state[4] && brd.state[4] == brd.state[6]) {
		if (brd.state[2] != 0) {
			return brd.state[2];// return the winner
		}
		//if (brd.state[2] == -1) {
		//	return -1;
		//}
		//else if (brd.state[2] == 1) {
		//	return 1;
		//}
	}

	return 0; // If no one has won the game then return 0 (draw)
	
} 

// Private makMove method
void XO::makeMove(const int8_t& play, const uint8_t& pos, BoardXO& brd)
{  
	// if the conditions are true and the move is valid then make the move 
	//if ((brd.numMoves < 9 && brd.state[pos] == 0) && (play == -1 || play == 1) && (brd.turn[brd.numMoves - 1] != play) && pos < 9 && !gameOver(brd) && pos >= 0) {
		brd.state[pos] = play; // update the private variables 
		brd.moves[brd.numMoves] = pos;
		brd.turn[brd.numMoves] = play;
		brd.numMoves = brd.numMoves + 1;
	//}
}
