#include "Puzzle.h"

Puzzle::Puzzle()
{
  startboard.SetLoper(Position({ 0, 0 }), Loper::BlackLoper());
  startboard.SetLoper(Position({ 1, 0 }), Loper::BlackLoper());
  startboard.SetLoper(Position({ 2, 0 }), Loper::BlackLoper());
  startboard.SetLoper(Position({ 3, 0 }), Loper::BlackLoper());

  startboard.SetLoper(Position({ 0, 4 }), Loper::WhiteLoper());
  startboard.SetLoper(Position({ 1, 4 }), Loper::WhiteLoper());
  startboard.SetLoper(Position({ 2, 4 }), Loper::WhiteLoper());
  startboard.SetLoper(Position({ 3, 4 }), Loper::WhiteLoper());

  targetboard.SetLoper(Position({ 0, 0 }), Loper::WhiteLoper());
  targetboard.SetLoper(Position({ 1, 0 }), Loper::WhiteLoper());
  targetboard.SetLoper(Position({ 2, 0 }), Loper::WhiteLoper());
  targetboard.SetLoper(Position({ 3, 0 }), Loper::WhiteLoper());

  targetboard.SetLoper(Position({ 0, 4 }), Loper::BlackLoper());
  targetboard.SetLoper(Position({ 1, 4 }), Loper::BlackLoper());
  targetboard.SetLoper(Position({ 2, 4 }), Loper::BlackLoper());
  targetboard.SetLoper(Position({ 3, 4 }), Loper::BlackLoper());
}

bool Puzzle::Move()
{
  // TODO: Add your implementation code here.
  return false;
}


bool Puzzle::Solve()
{
  std::set<LoperBoard> alreadyDone;
  Moves moves;

  return Solve(alreadyDone, moves);
}


bool Puzzle::Solve(std::set<LoperBoard>& alreadyDone, Moves& moves)
{
  for ()
  return false;
}
