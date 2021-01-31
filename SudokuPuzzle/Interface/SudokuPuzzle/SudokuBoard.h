#pragma once


#include "LoperLibrary/Board.h"

namespace sudoku
{
// Vakje for 6 * 9 sudoku:
// -------------
// | 0 | 1 | 2 |
// -------------
// | 3 | 4 | 5 |
// -------------
// Vakje for 9 * 9 sudoku:
// -------------
// | 0 | 1 | 2 |
// -------------
// | 3 | 4 | 5 |
// -------------
// | 6 | 7 | 8 |
// -------------
template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
class Sudoku : Board<int, ROWSPERVAKJE * COLUMSPERVAKJE, ROWSPERVAKJE * COLUMSPERVAKJE>
{
public:
  bool IsSafe(const Position& position, const int& piece) const override;
  bool Place(const int& piece, const Position& from, const Position& to) override;
  PositionSet ReachablePositions(const Position& position, const int& piece) const override;

private:
  using ParentBoard = Board<int, ROWSPERVAKJE* COLUMSPERVAKJE, ROWSPERVAKJE* COLUMSPERVAKJE>;
  using Collection = std::vector<int>;

  Collection GetRow(int row) const;
  Collection GetColumn(int column) const;
  Collection GetVakje(int vakje) const;

  bool IsRowSafe(int row, int newValue) const;
  bool IsColumnSafe(int column, int newValue) const;
  bool IsVakjeSafe(int vakje, int newValue) const;

  int GetVakje(const Position& position) const;

  const int mRowsAndColumns = ROWSPERVAKJE * COLUMSPERVAKJE;
};

template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
bool Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::IsSafe(const Position& position, const int& piece) const { return true; }

template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
bool Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::Place(const int& piece, const Position& from, const Position& to) { return true; }

template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
PositionSet Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::ReachablePositions(const Position& position, const int& piece) const { return PositionSet(); }

template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
typename Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::Collection Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::GetRow(int row) const
{
  Collection values;
  for (int c = 0; c < mRowsAndColumns; ++c) {
    std::optional<int> value(ParentBoard::GetPiece(Position({ row, c })));
    if (value)
      values.emplace_back(*value);
  }

  return values;
}

template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
typename Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::Collection Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::GetColumn(int column) const {
  Collection values;
  for (int r = 0; r < mRowsAndColumns; ++r) {
    std::optional<int> value(ParentBoard::GetPiece(Position({ r, column })));
    if (value)
      values.emplace_back(*value);
  }

  return values;
}

template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
typename Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::Collection Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::GetVakje(int vakje) const {
  Collection values;
  // vakjerow = vakje / columns
  // vakjecolumn = vakje % columns;
  // row = vakjerow * ROWSPERVAKJE to row = (vakjerow + 1) * ROWSPERVAKJE
  // column = vakjecolumn * COLUMSPERVAKJE to row = (vakjerow + 1) * ROWSPERVAKJE
  for (int r = vakje / ROWSPERVAKJE; r < (vakje + 1) * ROWSPERVAKJE; ++r) {
    for (int c = vakje % COLUMSPERVAKJE; c < (vakje) % COLUMSPERVAKJE + COLUMSPERVAKJE; ++c) {
      std::optional<int> value(ParentBoard::GetPiece(Position({ r, c })));
      if (value)
        values.emplace_back(*value);
    }
  }

  return values;
}

template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
bool Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::IsRowSafe(int row, int newValue) const
{
  Collection values(GetRow(row));
  return std::find(values.begin(), values.end(), newValue) == values.end();
}

template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
bool Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::IsColumnSafe(int column, int newValue) const
{
  Collection values(GetColumn(column));
  return std::find(values.begin(), values.end(), newValue) == values.end();
}

template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
bool Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::IsVakjeSafe(int vakje, int newValue) const
{
  Collection values(GetVakje(vakje));
  return std::find(values.begin(), values.end(), newValue) == values.end();
}

template <int ROWSPERVAKJE, int COLUMSPERVAKJE>
int Sudoku<ROWSPERVAKJE, COLUMSPERVAKJE>::GetVakje(const Position& position) const
{
  return position.row * mRowsAndColumns + position.column;
}

}