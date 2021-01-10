#include "Puzzle.h"

Puzzle::Puzzle()
{
  //startboard.SetLoper(Position({ 0, 0 }), Loper::BlackLoper());
  //startboard.SetLoper(Position({ 0, 3 }), Loper::WhiteLoper());

  //targetboard.SetLoper(Position({ 1, 0 }), Loper::WhiteLoper());
  //targetboard.SetLoper(Position({ 1, 3 }), Loper::BlackLoper());

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

bool Puzzle::MakeMove(const Move& move)
{
  return startboard.PlaceLoper(move.loper, move.from, move.to);
}

bool Puzzle::UndoMove(const Move& move)
{
  return startboard.PlaceLoper(move.loper, move.to, move.from);
}


static int stacksize;
bool Puzzle::Solve()
{
  LoperBoardSet alreadyDone;
  Moves moves;
  alreadyDone.insert(startboard);

  if (Solve(alreadyDone, moves, Loper::Colour::Black)) {
    if (!(startboard == targetboard))
      throw std::runtime_error("Incorrect solution");

    return true;
  }

  return false;
}


bool Puzzle::Solve(LoperBoardSet& alreadyDone, Moves& moves, Loper::Colour startColour)
{
  ++stacksize;
  LoperMap whiteLopers(startboard.GetLopers(startColour));
  for (const auto& loper : whiteLopers) {
    PositionSet positions(startboard.OpenPositions(loper.first));
    for (const auto& position : positions) {
      Move move({loper.second, loper.first, position });
      if (MakeMove(move)) {
        if (alreadyDone.find(startboard) != alreadyDone.end()) {
          UndoMove(move);
          continue;
        }

        // See whether we reached our goal:
        if (startboard == targetboard) {
          moves.push_back(move);
          return true;
        }

        moves.push_back(move);
        alreadyDone.insert(startboard);
        if (Solve(alreadyDone, moves, startColour == Loper::Colour::White ? Loper::Colour::Black : Loper::Colour::White))
          return true;

        UndoMove(move);
        moves.pop_back();
      }
    }
  }

  --stacksize;
  return false;
}
