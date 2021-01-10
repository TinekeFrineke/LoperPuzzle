#pragma once

#include <vector>

#include "Board.h"


class Puzzle
{
public:
  struct Move { Loper loper; Position from; Position to; bool operator==(const Move& move) const; };
  using Moves = std::vector<Move>;

  using LoperBoard = Board<4, 5>;

  using LoperBoardSet = std::set <LoperBoard>;


  Puzzle();

  bool MakeMove(const Move& move);
  bool Solve();

private:
  //bool ProcessMove(const Move& move, LoperBoardSet& alreadyDone, Moves& moves);
  bool Solve(LoperBoardSet& alreadyDone, Moves& moves, const unsigned int maxdepth);
  bool UndoMove(const Move& move);

  LoperBoard startboard;
  LoperBoard targetboard;
};
