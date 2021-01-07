#include <cstdlib>
#include <ctime>
#include "catch.hpp"
#include <memory>
#include "XO.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <exception>

//X = -1
//O = 1

TEST_CASE("Corner Play Test") {
	XO g;
	g.makeMove(-1, 0);
	while (!g.gameOver()) {
		g.makeOptimalMove();
		std::cout << std::endl;
		g.show();
		std::cout << std::endl;
	}
	std::cout << std::endl;
	g.show();
}
TEST_CASE("Corner Play Test 2") {
	std::cout << std::endl << "Test 2: " << std::endl;
	XO g;
	g.makeMove(-1, 0);
	g.makeMove(1, 4);
	//g.makeMove(-1, 1);
	//g.makeMove(1, 3);
	//g.makeMove(-1, 4);
	BoardXO brd = g.getBoard();
	while (!g.gameOver()) {
		g.makeOptimalMove();
		std::cout << std::endl;
		g.show();
		std::cout << std::endl;
	}
	g.show();
	REQUIRE(g.winner() == 0);
	REQUIRE(g.gameOver() == 1);
	REQUIRE(g.getBoard().numMoves == 9);
}

TEST_CASE("Player X immediate win")
{
	INFO("Player X eventual win");
	XO g;
	g.makeMove(-1, 2);
	g.makeMove(1, 0);
	g.makeMove(-1, 3);
	g.makeMove(1, 7);
	g.makeMove(-1, 6);
	g.makeMove(1, 8);

	g.show();

	while (!g.gameOver())
		g.makeOptimalMove();

	g.show();

	REQUIRE(g.winner() == -1);
	REQUIRE(g.getBoard().numMoves == 7);
}

TEST_CASE("Optimal block w/certain loss for O")
{
	INFO("Optimal block w/certain loss for O");
	XO g;
	g.makeMove(-1, 1);
	g.makeMove(1, 6);
	g.makeMove(-1, 5);
	g.makeMove(1, 7);
	g.makeMove(-1, 8);

	g.makeOptimalMove();

	g.show();

	REQUIRE(g.winner() == 0);
	REQUIRE(g.getBoard().numMoves == 6);
}

TEST_CASE("Player X eventual win")
{
	INFO("Player X eventual win");
	XO g;
	g.makeMove(-1, 1);
	g.makeMove(1, 6);
	g.makeMove(-1, 5);
	g.makeMove(1, 7);
	g.makeMove(-1, 8);
	std::cout << std::endl << "Test 4: " << std::endl;
	g.show();
	std::cout << std::endl;
	while (!g.gameOver()) {
		g.makeOptimalMove();
		std::cout << std::endl;
		g.show();
		std::cout << std::endl;
	}
	g.show();

	REQUIRE(g.winner() == -1);
	REQUIRE(g.getBoard().numMoves == 9);
}

TEST_CASE("Optimal block w/certain loss for X")
{
	INFO("Optimal block w/certain loss for X");
	XO g;
	g.makeMove(1, 1);
	g.makeMove(-1, 6);
	g.makeMove(1, 5);
	g.makeMove(-1, 7);
	g.makeMove(1, 8);

	// while(!g.gameOver())
	//   g.makeOptimalMove();

	g.makeOptimalMove();

	g.show();

	REQUIRE(g.winner() == 0);
	REQUIRE(g.getBoard().numMoves == 6);
}

TEST_CASE("Player O eventual win")
{
	INFO("Player O eventual win");
	XO g;
	g.makeMove(1, 1);
	g.makeMove(-1, 6);
	g.makeMove(1, 5);
	g.makeMove(-1, 7);
	g.makeMove(1, 8);
	std::cout << std::endl << "Test 3: " << std::endl;
	g.show();
	XO c(g.getBoard().turn, g.getBoard().moves, g.getBoard().numMoves);
	std::cout << std::endl;
	while (!c.gameOver()) {
		c.makeOptimalMove();
		std::cout << std::endl;
		c.show();
		std::cout << std::endl;
	}

	c.show();

	REQUIRE(c.winner() == 1);
	REQUIRE(c.getBoard().numMoves == 9);
}

/*
TEST_CASE("Failing tests") {
	XO g; 
	g.makeMove(-1, 0);
	g.makeMove(1, 2);
	g.makeMove(-1, 1);
	g.makeMove(1, 3);
	g.makeMove(-1, 5);
	g.makeMove(1, 4);
	g.makeMove(-1, 6);
	g.makeMove(1, 7);
	g.makeMove(-1, 8);
	g.show();
	std::cout << "Winner: " << int(g.winner()) << std::endl;
	std::cout << "Game state: " << g.gameOver() << std::endl;


}


TEST_CASE( "Player X immediate win" )
{
	INFO( "Player X eventual win" );
	XO g;
	g.makeMove(-1,2);	
	g.makeMove(1,0);
	g.makeMove(-1,3);
	g.makeMove(1,7);
	g.makeMove(-1,6);
	g.makeMove(1,8);
	g.makeMove(-1, 1);
	g.makeMove(1, 4);
	//g.makeMove(-1, 5);
	//std::cout <<" mod: "<<  (2%3)  << std::endl;
	g.show();
	
	//while(!g.gameOver())
	//  g.makeOptimalMove();
	std::cout << "Winner: " << int(g.winner()) << std::endl;
	std::cout << "Game state: " << g.gameOver() << std::endl;
	//g.show();
	
	//REQUIRE(g.winner() == -1);
	//REQUIRE(g.getBoard().numMoves == 7);
}

TEST_CASE( "Optimal block w/certain loss for O" )
{
	INFO( "Optimal block w/certain loss for O" );
	XO g;
	g.makeMove(-1,1);
	g.makeMove(1,6);
	g.makeMove(-1,5);
	g.makeMove(1,7);
	g.makeMove(-1,8);

	//g.makeOptimalMove();
	
	//g.show();
	
	//REQUIRE(g.winner() == 0);
	//REQUIRE(g.getBoard().numMoves == 6);
}

TEST_CASE( "Player X eventual win" )
{
	INFO( "Player X eventual win" );
	XO g;
	g.makeMove(-1,1);
	g.makeMove(1,6);
	g.makeMove(-1,5);
	g.makeMove(1,7);
	g.makeMove(-1,8);
	g.makeMove(1, 2);
	g.makeMove(-1, 4);
	g.makeMove(1, 3);
	g.makeMove(-1, 0);
	//g.makeMove(1, 5);
	g.show();
	std::cout << "Winner: " << int(g.winner()) << std::endl;
	std::cout << "Game state: " << g.gameOver() << std::endl;
	BoardXO brd;
	brd.numMoves = g.getBoard().numMoves;;
	for (int i = 0; i < 9; i++) {
		brd.state[i] = g.getBoard().state[i];
	}
	for (int i = 0; i < brd.numMoves; i++) {
		brd.moves[i] = g.getBoard().moves[i];
		brd.turn[i] = g.getBoard().turn[i];
	}
	//brd.turn[1] = -1;
	//while(!g.gameOver()){}
	//  g.makeOptimalMove();
	//brd.turn[1] = -1;
	//brd.moves[2] = 8;
	//g.show();
	//XO c;
	//c.makeMoves(brd.turn, brd.moves, brd.numMoves);
	//c.makeMoves(brd.turn, brd.moves, brd.numMoves);
	//REQUIRE_FALSE(c.makeMoves(brd.turn, brd.moves, brd.numMoves));
	//REQUIRE(c.getBoard().numMoves == 0);
	//c.show();

	//REQUIRE(g.winner() == -1);
	//REQUIRE(g.getBoard().numMoves == 9);
}

TEST_CASE( "Optimal block w/certain loss for X" )
{
	INFO( "Optimal block w/certain loss for X" );
	XO g;
	g.makeMove(1,1);
	g.makeMove(-1,6);
	g.makeMove(1,5);
	g.makeMove(-1,7);
	g.makeMove(1,8);

	// while(!g.gameOver())
	//   g.makeOptimalMove();

	//g.makeOptimalMove();
	
	g.show();
	
	//REQUIRE(g.winner() == 0);
//	REQUIRE(g.getBoard().numMoves == 6);
}

TEST_CASE( "Player O eventual win" )
{
	INFO( "Player O eventual win" );
	XO g;
	g.makeMove(1,1);
	g.makeMove(-1,6);
	g.makeMove(1,5);
	g.makeMove(-1,7);
	g.makeMove(1,8);

	//while(!g.gameOver())
	//  g.makeOptimalMove();
	
	g.show();
	
	//REQUIRE(g.winner() == 1);
	//REQUIRE(g.getBoard().numMoves == 9);
}
*/