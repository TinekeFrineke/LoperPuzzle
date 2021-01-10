#include "Puzzle.h"

#include <iostream>

namespace
{
class PuzzleException
{
};

void Print(const Puzzle::Moves& moves)
{
  for (const auto& move : moves)
    std::cout << (move.loper.colour == Loper::Colour::White ? "White" : "Black")
    << " bisshop from row " << move.from.row << " col " << move.from.column
    << " to row " << move.to.row << " col " << move.to.column << std::endl;
}
}

bool Puzzle::Move::operator==(const Move& move) const
{
  return loper == move.loper && from == move.from && to == move.to;
}


Puzzle::Puzzle()
{
  //startboard.SetLoper(Position({ 0, 0 }), Loper::BlackLoper());
  //startboard.SetLoper(Position({ 0, 3 }), Loper::WhiteLoper());

  //targetboard.SetLoper(Position({ 1, 0 }), Loper::WhiteLoper());
  //targetboard.SetLoper(Position({ 1, 3 }), Loper::BlackLoper());

  // Part 1:
  startboard.SetLoper(Position({ 0, 0 }), Loper::BlackLoper());
  startboard.SetLoper(Position({ 2, 0 }), Loper::BlackLoper());

  startboard.SetLoper(Position({ 0, 4 }), Loper::WhiteLoper());
  startboard.SetLoper(Position({ 2, 4 }), Loper::WhiteLoper());

  targetboard.SetLoper(Position({ 0, 0 }), Loper::WhiteLoper());
  targetboard.SetLoper(Position({ 2, 0 }), Loper::WhiteLoper());

  targetboard.SetLoper(Position({ 0, 4 }), Loper::BlackLoper());
  targetboard.SetLoper(Position({ 2, 4 }), Loper::BlackLoper());

  const bool result(Solve());

  startboard.Clear();
  targetboard.Clear();

  // Part 2:
  startboard.SetLoper(Position({ 1, 0 }), Loper::BlackLoper());
  startboard.SetLoper(Position({ 3, 0 }), Loper::BlackLoper());

  startboard.SetLoper(Position({ 1, 4 }), Loper::WhiteLoper());
  startboard.SetLoper(Position({ 3, 4 }), Loper::WhiteLoper());

  targetboard.SetLoper(Position({ 1, 0 }), Loper::WhiteLoper());
  targetboard.SetLoper(Position({ 3, 0 }), Loper::WhiteLoper());

  targetboard.SetLoper(Position({ 1, 4 }), Loper::BlackLoper());
  targetboard.SetLoper(Position({ 3, 4 }), Loper::BlackLoper());

  Solve();
}

bool Puzzle::MakeMove(const Move& move)
{
  return startboard.PlaceLoper(move.loper, move.from, move.to);
}

bool Puzzle::UndoMove(const Move& move)
{
  return startboard.PlaceLoper(move.loper, move.to, move.from);
}


static int stacksize = 0;
bool Puzzle::Solve()
{
  for (int i = 4; i < 100; ++i) {
    try {
      LoperBoardSet alreadyDone;
      Moves moves;
      alreadyDone.insert(startboard);

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


//bool Puzzle::ProcessMove(const Move& move, LoperBoardSet& alreadyDone, Moves& moves)
//{
//}


bool Puzzle::Solve(LoperBoardSet& alreadyDone, Moves& moves, const unsigned int maxdepth)
{
  /**/

  //bool debug = (moves == Moves({ Move({Loper::Colour::Black, Position({0, 0}), Position({1, 1})}),
  //                               Move({Loper::Colour::White, Position({0, 4}), Position({1, 3})}),
  //                               Move({Loper::Colour::Black, Position({1, 1}), Position({0, 0})}),
  //                               Move({Loper::Colour::Black, Position({2, 0}), Position({1, 1})}),
  //                               Move({Loper::Colour::White, Position({1, 3}), Position({0, 4})}),
  //                               Move({Loper::Colour::White, Position({0, 4}), Position({3, 1})}),
  //                               Move({Loper::Colour::White, Position({2, 4}), Position({1, 3})}) } ));

  /**/
  ++stacksize;
  if (moves.size() >= maxdepth)
    return false;

  LoperMap lopers(startboard.GetLopers());
  for (const auto& loper : lopers) {
    //if (debug)
    //  debug = false;
    PositionSet positions(startboard.ReachablePositions(loper.first, loper.second));
    for (const auto& position : positions) {
      Move move({ loper.second, loper.first, position });
      if (MakeMove(move)) {
        if (alreadyDone.find(startboard) != alreadyDone.end()) {
          UndoMove(move);
          continue;
        }

        moves.push_back(move);

        // See whether we reached our goal:
        if (startboard == targetboard)
          return true;

        alreadyDone.insert(startboard);
        if (Solve(alreadyDone, moves, maxdepth))
          return true;

        UndoMove(move);
        moves.pop_back();
      }
    }
  }

  --stacksize;
  return false;
}
