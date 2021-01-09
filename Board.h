#pragma once

#include <map>
#include <optional>
#include <stdexcept>
#include <set>

#include "Loper.h"

template <int ROWS, int COLUMNS>
bool IsValid(const Position& position)
{
  return position.row >= 0 && position.row < ROWS&& position.column >= 0 && position.column < COLUMNS;
}

template <int ROWS, int COLUMNS>
std::set<Position> ReachablePositions(const Position& position)
{
  std::set<Position> positions;
  if (ROWS < COLUMNS) {
    for (int row = 0; row < ROWS; ++row) {
      positions.insert(Position({ row, position.column + position.row - row }));
      positions.insert(Position({ row, position.column - position.row + row }));
    }
  }
  else {
    for (int column = 0; column < COLUMNS; ++column) {
      positions.insert(Position({ position.row + position.column - column, column }));
      positions.insert(Position({ position.row - position.column + column, column }));
    }
  }

  return position.row >= 0 && position.row < ROWS&& position.column >= 0 && position.column < COLUMNS;
}

template <int ROWS, int COLUMNS>
class Board
{
public:

  Board();

  std::optional<Loper> GetLoper(const Position& position) const;
  bool PlaceLoper(const Loper& loper, const Position& from, const Position& to);
  void ClearLoper(const Position& position);
  void SetLoper(const Position& position, const Loper& loper);

  LoperMap GetLopers() const;

private:
  using Row = std::optional<Loper>[COLUMNS];
  Row board[ROWS];

  LoperMap lopers;
};

template <int ROWS, int COLUMNS>
inline Board<ROWS, COLUMNS>::Board()
{
}

template <int ROWS, int COLUMNS>
inline std::optional<Loper> Board<ROWS, COLUMNS>::GetLoper(const Position& position) const
{
  if (!IsValid<ROWS, COLUMNS>(position))
    throw std::runtime_error("row or clum out of range");

  return lopers[position.row][position.column];
}

template <int ROWS, int COLUMNS>
inline bool Board<ROWS, COLUMNS>::PlaceLoper(const Loper& loper, const Position& from, const Position& to)
{
  if (!IsValid<ROWS, COLUMNS>(from))
    throw std::runtime_error("from: row or clum out of range");
  if (!IsValid<ROWS, COLUMNS>(to))
    throw std::runtime_error("from: row or clum out of range");

  std::optional<Loper> loperFrom = GetLoper(from);
  if (!loperFrom)
    throw std::runtime_error("loper not found");

  std::optional<Loper> loperTo = GetLoper(to);
  if (loperTo)
    return false;

  std::set<Position> positions(ReachablePositions<ROWS, COLUMNS>(to));

  for (const auto position : positions) {
    auto result = std::find(positions.begin(), positions.end(), position);
    if (position != from && GetLoper(position))
      return false;
  }

  ClearLoper(from);


  return true;
}

template <int ROWS, int COLUMNS>
inline void Board<ROWS, COLUMNS>::ClearLoper(const Position& position)
{
  board[position.row][position.column] = std::nullopt_t;
}

template <int ROWS, int COLUMNS>
inline void Board<ROWS, COLUMNS>::SetLoper(const Position& position, const Loper& loper)
{
  board[position.row][position.column] = loper;
}

template<int ROWS, int COLUMNS>
inline Board<ROWS, COLUMNS>::LoperMap Board<ROWS, COLUMNS>::GetLopers() const
{
  return lopers;
}

template <int ROWS, int COLUMNS>
inline bool operator==(const Board<ROWS, COLUMNS>& lhs, const Board<ROWS, COLUMNS>& rhs)
{
  for (auto column : COLUMNS) {
    for (auto row : ROWS) {
      if (lhs[row][column] != rhs[row][column])
        return false;
    }
  }

  return true;
}