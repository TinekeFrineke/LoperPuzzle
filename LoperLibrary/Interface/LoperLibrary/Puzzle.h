#pragma once

#include <vector>

#include "KnightBoard.h"
#include "LoperBoard.h"


class Puzzle
{
public:
  struct Move { loper::Colour loper; Position from; Position to; bool operator==(const Move& move) const; };
  using Moves = std::vector<Move>;

  using MyBoard = LoperBoard<4, 5>;

  using MyBoardSet = std::set<MyBoard>;
  using MyBoardMoves = std::map<MyBoard, size_t>;

  Puzzle(const MyBoard& start, const MyBoard& target);

  void SetStart(const MyBoard& board);
  void SetTarget(const MyBoard& board);

  MyBoard GetStart() const { return startboard; }
  MyBoard GetTarget() const { return targetboard; }

  bool MakeMove(const Move& move);
  bool Solve();
  bool Solve(MyBoardMoves& alreadyDone, Moves& moves, const unsigned int maxdepth);

private:
  bool UndoMove(const Move& move);

  MyBoard startboard;
  MyBoard targetboard;
};
