#pragma once

#include <vector>

#include "Board.h"

class Puzzle
{
public:
  struct Move { Loper loper; Position from; Position to; };
  using Moves = std::vector<Move>;

  using LoperBoard = Board<4, 5>;
  Puzzle();

  bool Move();
  bool Solve();

private:
  bool Solve(std::set<LoperBoard>& alreadyDone, Moves& moves);

  LoperBoard startboard;
  LoperBoard targetboard;
};

