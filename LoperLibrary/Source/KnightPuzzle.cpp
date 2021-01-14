
#include "KnightPuzzle.h"

#include <iostream>

namespace
{

void Print(const knight::Puzzle::Moves& moves)
{
  for (const auto& move : moves)
    std::cout << (move.knight == knight::Colour::White ? "White" : move.knight == knight::Colour::Black ? "Black" : "Fixed")
    << " bisshop from row " << move.from.row << " col " << move.from.column
    << " to row " << move.to.row << " col " << move.to.column << std::endl;
}
}

namespace knight
{
bool Puzzle::Move::operator==(const Move& move) const
{
  return knight == move.knight && from == move.from && to == move.to;
}


Puzzle::Puzzle(const MyBoard& start, const MyBoard& target)
{
  SetStart(start);
  SetTarget(target);
}

void Puzzle::SetStart(const MyBoard& board)
{
  startboard = board;
}

void Puzzle::SetTarget(const MyBoard& board)
{
  targetboard = board;
}

bool Puzzle::MakeMove(const Move& move)
{
  return startboard.Place(Knight(move.knight), move.from, move.to);
}

bool Puzzle::UndoMove(const Move& move)
{
  return startboard.Place(Knight(move.knight), move.to, move.from);
}


static int stacksize = 0;
bool Puzzle::Solve(const int minimumIterations, const int maximumIterations)
{
  for (int i = minimumIterations; i <= maximumIterations; ++i) {
    try {
      MyBoardMoves alreadyDone;
      Moves moves;
      alreadyDone[startboard] = 0;

      if (Solve(alreadyDone, moves, i)) {
        if (!(startboard == targetboard))
          throw std::runtime_error("Incorrect solution");

        Print(moves);
        return true;
      }
    }
    catch (const PuzzleException&) {
      // Nothing found...
    }
  }

  return false;
}

/*
expected:
White bisshop from row 0 col 4 to row 1 col 3
Black bisshop from row 2 col 0 to row 1 col 1
White bisshop from row 1 col 3 to row 0 col 4
White bisshop from row 0 col 4 to row 3 col 1
actual:
Black bisshop from row 0 col 0 to row 1 col 1
White bisshop from row 0 col 4 to row 1 col 3
Black bisshop from row 1 col 1 to row 0 col 0
Black bisshop from row 2 col 0 to row 1 col 1
White bisshop from row 1 col 3 to row 0 col 4
White bisshop from row 0 col 4 to row 3 col 1
*/

bool Puzzle::Solve(MyBoardMoves& alreadyDone, Moves& moves, const unsigned int maxdepth) {
  static int stackdepth = 0;
  ++stackdepth;
  std::cout << "stackdepth: " << stackdepth << std::endl;

  KnightMap knights(startboard.GetPieces());
  for (const auto& knight : knights) {
    PositionSet positions(startboard.ReachablePositions(knight.first, knight.second));
    for (const auto& position : positions) {
      Move move({ knight.second.GetColour(), knight.first, position });
      if (MakeMove(move)) {
        auto findResult(alreadyDone.find(startboard));
        if (findResult != alreadyDone.end()) {
          if (findResult->second > moves.size() + 1) {
            findResult->second = moves.size() + 1;
          }
          else {
            UndoMove(move);
            continue;
          }
        }

        moves.push_back(move);

        // See whether we reached our goal:
        if (startboard == targetboard)
          return true;

        if (moves.size() >= maxdepth) {
          UndoMove(move);
          moves.pop_back();
          continue;
        }

        alreadyDone[startboard] = moves.size();
        if (Solve(alreadyDone, moves, maxdepth))
          return true;

        UndoMove(move);
        moves.pop_back();
      }
    }
  }

  --stackdepth;
  return false;
}
} // namespace knight