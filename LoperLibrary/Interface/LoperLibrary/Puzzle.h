#pragma once

#include <vector>

#include "Board.h"


class Puzzle
{
public:
  struct Move { loper::Colour loper; Position from; Position to; bool operator==(const Move& move) const; };
  using Moves = std::vector<Move>;

  using LoperBoard = Board<4, 5>;

  using LoperBoardSet = std::set<LoperBoard>;
  using LoperBoardMoves = std::map<LoperBoard, int>;

  Puzzle(const LoperBoard& start, const LoperBoard& target);

  void SetStart(const LoperBoard& board);
  void SetTarget(const LoperBoard& board);

  LoperBoard GetStart() const { return startboard; }
  LoperBoard GetTarget() const { return targetboard; }

  bool MakeMove(const Move& move);
  bool Solve();
  bool Solve(LoperBoardMoves& alreadyDone, Moves& moves, const unsigned int maxdepth);

private:
  bool UndoMove(const Move& move);

  LoperBoard startboard;
  LoperBoard targetboard;
};
