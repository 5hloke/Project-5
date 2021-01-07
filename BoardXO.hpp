#ifndef BOARDXO_HPP
#define BOARDXO_HPP

#include <iostream>
#include <string>

// A board struct for the game tic-tac-toe
struct BoardXO
{
  int8_t state[9]; //where player markers are on the board (player can be -1 or 1; 0 for unoccupied)
  uint8_t moves[9];  //sequence of moves that led to current game state (i.e., which marker position players selected)
  int8_t turn[9]; //which player made the corresponding move
  uint8_t numMoves; //total number of moves that have been made in the game to this point
  uint32_t id; //a key (unique number) that one can assign to, and use to refer to, this particular board

  /* default constructor  
     @return a blank board (all positions unoccupied; i.e., 0 and numMoves = 0)*/
  BoardXO()
  {
      state[0] = 0;
      state[1] = 0;
      state[2] = 0;
      state[3] = 0;
      state[4] = 0;
      state[5] = 0;
      state[6] = 0;
      state[7] = 0;
      state[8] = 0;

      numMoves = 0;
      id = 0;
      

  }
    
  /* return marker for requested position
     @return the marker at the given position (-1, 0, 1) throw std::range_error is subscript is out of bounds*/
  const int8_t& operator[](std::uint8_t idx) const
  {
     if (idx >= 9) {
          throw std::range_error("Array Index out of bounds");
     }
      return state[idx];
  }

  friend std::ostream& operator<<(std::ostream& os, const BoardXO& brd)
  {
      int count = 0;
      for (int i = 0; i < 9; i++)
      {

          if (i % 3 == 0 && count>0) {
              os << std::endl;
              count = 0;
          }
          if (brd.state[i] == -1) {
              os << "X";
          }
          else if (brd.state[i] == 0) {
              os << " ";
          }
          else if (brd.state[i] == 1) {
              os << "O";
          }
          count++; 
      }

      os << std::endl;

      return os;
  }
};

#endif
