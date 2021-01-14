// LoperPuzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "LoperLibrary/LoperPuzzle.h"
#include "LoperLibrary/KnightPuzzle.h"

namespace
{
void Print(const loper::Puzzle::Moves& moves)
{
  for (const auto& move : moves)
    std::cout << (move.loper == loper::Colour::White ? "White" : "Black")
    << " bisshop from row " << move.from.row << " col " << move.from.column
    << " to row " << move.to.row << " col " << move.to.column << std::endl;
}

bool SolvePuzzle(loper::Puzzle& puzzle, loper::Puzzle::Moves& moves)
{
  for (int i = 4; i < 100; ++i) {
    try {
      moves.clear();
      loper::Puzzle::MyBoardMoves alreadyDone;
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

void Print(const knight::Puzzle::Moves& moves) {
  for (const auto& move : moves)
    std::cout << (move.knight == knight::Colour::White ? "White" : "Black")
    << " bisshop from row " << move.from.row << " col " << move.from.column
    << " to row " << move.to.row << " col " << move.to.column << std::endl;
}

bool SolvePuzzle(knight::Puzzle& puzzle, knight::Puzzle::Moves& moves) {
  for (int i = 4; i < 100; ++i) {
    try {
      moves.clear();
      knight::Puzzle::MyBoardMoves alreadyDone;
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

void loperPuzzle()
{
  loper::Puzzle::MyBoard startboard;
  loper::Puzzle::MyBoard targetboard;

  startboard.SetPiece(Position({ 0, 0 }), loper::Colour::Black);
  startboard.SetPiece(Position({ 2, 0 }), loper::Colour::Black);

  startboard.SetPiece(Position({ 0, 4 }), loper::Colour::White);
  startboard.SetPiece(Position({ 2, 4 }), loper::Colour::White);

  targetboard.SetPiece(Position({ 0, 0 }), loper::Colour::White);
  targetboard.SetPiece(Position({ 2, 0 }), loper::Colour::White);

  targetboard.SetPiece(Position({ 0, 4 }), loper::Colour::Black);
  targetboard.SetPiece(Position({ 2, 4 }), loper::Colour::Black);

  loper::Puzzle puzzle(startboard, targetboard);
  loper::Puzzle::Moves moves;
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
}

void knightPuzzle() {
  knight::Puzzle::MyBoard startboard;
  knight::Puzzle::MyBoard targetboard;

  startboard.SetPiece(Position({ 0, 1 }), knight::Knight(knight::Colour::Fixed));
  startboard.SetPiece(Position({ 0, 2 }), knight::Knight(knight::Colour::Fixed));
  startboard.SetPiece(Position({ 0, 3 }), knight::Knight(knight::Colour::Fixed));
  startboard.SetPiece(Position({ 2, 3 }), knight::Knight(knight::Colour::Fixed));
  startboard.SetPiece(Position({ 3, 2 }), knight::Knight(knight::Colour::Fixed));
  startboard.SetPiece(Position({ 3, 3 }), knight::Knight(knight::Colour::Fixed));

  startboard.SetPiece(Position({ 0, 0 }), knight::Knight(knight::Colour::Black));
  startboard.SetPiece(Position({ 2, 0 }), knight::Knight(knight::Colour::Black));

  startboard.SetPiece(Position({ 1, 3 }), knight::Knight(knight::Colour::White));
  startboard.SetPiece(Position({ 2, 1 }), knight::Knight(knight::Colour::White));

  targetboard.SetPiece(Position({ 0, 1 }), knight::Knight(knight::Colour::Fixed));
  targetboard.SetPiece(Position({ 0, 2 }), knight::Knight(knight::Colour::Fixed));
  targetboard.SetPiece(Position({ 0, 3 }), knight::Knight(knight::Colour::Fixed));
  targetboard.SetPiece(Position({ 2, 3 }), knight::Knight(knight::Colour::Fixed));
  targetboard.SetPiece(Position({ 3, 2 }), knight::Knight(knight::Colour::Fixed));
  targetboard.SetPiece(Position({ 3, 3 }), knight::Knight(knight::Colour::Fixed));

  targetboard.SetPiece(Position({ 0, 0 }), knight::Knight(knight::Colour::White));
  targetboard.SetPiece(Position({ 2, 0 }), knight::Knight(knight::Colour::White));

  targetboard.SetPiece(Position({ 1, 3 }), knight::Knight(knight::Colour::Black));
  targetboard.SetPiece(Position({ 2, 1 }), knight::Knight(knight::Colour::Black));

  knight::Puzzle puzzle(startboard, targetboard);
  knight::Puzzle::Moves moves;
  SolvePuzzle(puzzle, moves);
}

int main()
{
  knightPuzzle();
  
  return 0;
}
