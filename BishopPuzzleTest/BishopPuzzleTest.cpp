// BishopPuzzleTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "LoperLibrary/Puzzle.h"
#include <cassert>

namespace
{
void Print(const Puzzle::Moves& moves)
{
  for (const auto& move : moves)
    std::cout << (move.loper == loper::Colour::White ? "White" : "Black")
    << " bisshop from row " << move.from.row << " col " << move.from.column
    << " to row " << move.to.row << " col " << move.to.column << std::endl;
}

bool SolvePuzzle(Puzzle& puzzle, Puzzle::Moves& moves)
{
  for (int i = 4; i < 100; ++i) {
    try {
      moves.clear();
      Puzzle::LoperBoardMoves alreadyDone;
      alreadyDone[puzzle.GetStart()] = 0;

      if (puzzle.Solve(alreadyDone, moves, i)) {
        if (!(puzzle.GetStart() == puzzle.GetTarget()))
          throw std::runtime_error("Incorrect solution");

        Print(moves);
        return true;
      }
    }
    catch (const PuzzleException&) {
      // Nothing found...
      return false;
    }
  }

  return true;
}

void Test1()
{
  Puzzle::LoperBoard startboard;
  Puzzle::LoperBoard targetboard;

  startboard.SetLoper(Position({ 0, 0 }), loper::Colour::Black);
  startboard.SetLoper(Position({ 2, 0 }), loper::Colour::Black);

  startboard.SetLoper(Position({ 0, 4 }), loper::Colour::White);
  startboard.SetLoper(Position({ 2, 4 }), loper::Colour::White);

  targetboard.SetLoper(Position({ 3, 1 }), loper::Colour::White);
  targetboard.SetLoper(Position({ 0, 4 }), loper::Colour::White);

  targetboard.SetLoper(Position({ 1, 1 }), loper::Colour::Black);
  targetboard.SetLoper(Position({ 3, 3 }), loper::Colour::Black);

  Puzzle puzzle(startboard, targetboard);
  Puzzle::Moves moves;
  const bool solved(SolvePuzzle(puzzle, moves));
  assert(solved);

  assert(moves.size() == 4);
  assert(moves[0] == Puzzle::Move({ loper::Colour::White, Position({2, 4}), Position({1, 3}) }));
  assert(moves[1] == Puzzle::Move({ loper::Colour::Black, Position({0, 0}), Position({3, 3}) }));
  assert(moves[2] == Puzzle::Move({ loper::Colour::Black, Position({2, 0}), Position({1, 1}) }));
  assert(moves[3] == Puzzle::Move({ loper::Colour::White, Position({1, 3}), Position({3, 1}) }));
}
}

int main()
{
  Test1();
}
