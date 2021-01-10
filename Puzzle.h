#pragma once

#include <vector>

#include "Board.h"


class Puzzle
{
public:
  struct Move { Loper loper; Position from; Position to; };
  using Moves = std::vector<Move>;

  using LoperBoard = Board<4, 5>;

  using LoperBoardSet = std::set <LoperBoard>;


  Puzzle();

  bool MakeMove(const Move& move);
  bool Solve();

private:
  bool Solve(LoperBoardSet& alreadyDone, Moves& moves, Loper::Colour startColour);
  bool UndoMove(const Move& move);

  LoperBoard startboard;
  LoperBoard targetboard;
};
