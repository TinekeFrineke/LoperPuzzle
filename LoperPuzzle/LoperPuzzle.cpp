// LoperPuzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "LoperLibrary/Puzzle.h"

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
      Puzzle::MyBoardMoves alreadyDone;
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
}

int main()
{
  Puzzle::MyBoard startboard;
  Puzzle::MyBoard targetboard;

  startboard.SetPiece(Position({ 0, 0 }), loper::Colour::Black);
  startboard.SetPiece(Position({ 2, 0 }), loper::Colour::Black);

  startboard.SetPiece(Position({ 0, 4 }), loper::Colour::White);
  startboard.SetPiece(Position({ 2, 4 }), loper::Colour::White);

  targetboard.SetPiece(Position({ 0, 0 }), loper::Colour::White);
  targetboard.SetPiece(Position({ 2, 0 }), loper::Colour::White);

  targetboard.SetPiece(Position({ 0, 4 }), loper::Colour::Black);
  targetboard.SetPiece(Position({ 2, 4 }), loper::Colour::Black);

  Puzzle puzzle(startboard, targetboard);
  Puzzle::Moves moves;
  SolvePuzzle(puzzle, moves);

  startboard.Clear();
  targetboard.Clear();

  // Part 2:
  startboard.SetPiece(Position({ 1, 0 }), loper::Colour::Black);
  startboard.SetPiece(Position({ 3, 0 }), loper::Colour::Black);

  startboard.SetPiece(Position({ 1, 4 }), loper::Colour::White);
  startboard.SetPiece(Position({ 3, 4 }), loper::Colour::White);

  targetboard.SetPiece(Position({ 1, 0 }), loper::Colour::White);
  targetboard.SetPiece(Position({ 3, 0 }), loper::Colour::White);
  
  targetboard.SetPiece(Position({ 1, 4 }), loper::Colour::Black);
  targetboard.SetPiece(Position({ 3, 4 }), loper::Colour::Black);

  puzzle.SetStart(startboard);
  puzzle.SetTarget(targetboard);
  moves.clear();
  SolvePuzzle(puzzle, moves);

  return 0;
}
