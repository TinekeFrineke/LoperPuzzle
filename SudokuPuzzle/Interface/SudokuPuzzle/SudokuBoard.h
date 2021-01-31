#pragma once


#include "LoperLibrary/Board.h"

namespace sudoku
{
template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
class Sudoku : Board<int, ROWSPERVAKJE * COLUMSPERVAKJE, ROWSPERVAKJE * COLUMSPERVAKJE>
{
public:
  bool IsSafe(const Position& position, const int& piece) const override;
  bool Place(const int& piece, const Position& from, const Position& to) override;
  PositionSet ReachablePositions(const Position& position, const int& piece) const override;

  const int mRowsAndColumns = ROWSPERVAKJE * COLUMSPERVAKJE;
};

template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
bool Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::IsSafe(const Position& position, const int& piece) const { return true; }

template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
bool Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::Place(const int& piece, const Position& from, const Position& to) { return true; }

template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
PositionSet Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::ReachablePositions(const Position& position, const int& piece) const { return PositionSet(); }
}