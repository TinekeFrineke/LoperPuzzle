// KnightPuzzleTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "LoperLibrary/KnightPuzzle.h"
#include <cassert>


void EqualityTest()
{
  knight::Puzzle<4, 4>::MyBoard startboard;
  knight::Puzzle<4, 4>::MyBoard targetboard;

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

  targetboard.SetPiece(Position({ 0, 0 }), knight::Knight(knight::Colour::Black));
  targetboard.SetPiece(Position({ 2, 0 }), knight::Knight(knight::Colour::Black));

  targetboard.SetPiece(Position({ 1, 3 }), knight::Knight(knight::Colour::White));
  targetboard.SetPiece(Position({ 2, 1 }), knight::Knight(knight::Colour::White));

  assert(startboard == targetboard);
}

void UnEqualityTest() {
  knight::Puzzle<4, 4>::MyBoard startboard;
  knight::Puzzle<4, 4>::MyBoard targetboard;

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

  assert(!(startboard == targetboard));
}

void SmallTest()
{
  knight::Puzzle<3, 3>::MyBoard startboard;
  knight::Puzzle<3, 3>::MyBoard targetboard;
  startboard.SetPiece(Position({ 0, 0 }), knight::Knight(knight::Colour::White));
  targetboard.SetPiece(Position({ 1, 2 }), knight::Knight(knight::Colour::White));

  knight::Puzzle<3, 3> puzzle(startboard, targetboard);
  puzzle.Solve(0, 3);
}

void SmallTest2() {
  knight::Puzzle<3, 3>::MyBoard startboard;
  knight::Puzzle<3, 3>::MyBoard targetboard;
  startboard.SetPiece(Position({ 0, 0 }), knight::Knight(knight::Colour::White));
  targetboard.SetPiece(Position({ 2, 0 }), knight::Knight(knight::Colour::White));

  knight::Puzzle<3, 3> puzzle(startboard, targetboard);
  puzzle.Solve(0, 3);
}

int main()
{
  EqualityTest();
  UnEqualityTest();
  SmallTest();
  SmallTest2();

  return 0;
}