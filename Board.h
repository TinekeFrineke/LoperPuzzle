#pragma once

#include <optional>
#include <set>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

#include "LoperMap.h"

using PositionSet = std::set<Position>;

template <int ROWS, int COLUMNS>
bool IsValid(const Position& position)
{
  return position.row >= 0 && position.row < ROWS&& position.column >= 0 && position.column < COLUMNS;
}

template <int ROWS, int COLUMNS>
void AddValidPosition(const Position& position, PositionSet& positions)
{
  if (IsValid<ROWS, COLUMNS>(position))
    positions.insert(position);
}

template <int ROWS, int COLUMNS>
PositionSet ReachablePositions(const Position& position)
{
  PositionSet positions;
  if (ROWS < COLUMNS) {
    for (int row = 0; row < ROWS; ++row) {
      if (row == position.row)
        continue;
      AddValidPosition<ROWS, COLUMNS>(Position({ row, position.column + position.row - row }), positions);
      AddValidPosition<ROWS, COLUMNS>(Position({ row, position.column - position.row + row }), positions);
    }
  }
  else {
    for (int column = 0; column < COLUMNS; ++column) {
      if (column == position.column)
        continue;
      AddValidPosition<ROWS, COLUMNS>(Position({ position.row + position.column - column, column }), positions);
      AddValidPosition<ROWS, COLUMNS>(Position({ position.row - position.column + column, column }), positions);
    }
  }

  return positions;
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
  PositionSet OpenPositions(const Position& from) const;

  //LoperMap GetLopers() const;
  LoperMap GetLopers(Loper::Colour colour) const;

  bool operator<(const Board<ROWS, COLUMNS>& rhs) const { return lopers < rhs.lopers; }
  bool operator==(const Board<ROWS, COLUMNS>& rhs) const { return lopers == rhs.lopers; }
  bool Equals(const Board<ROWS, COLUMNS>& rhs) const { return lopers == rhs.lopers; }

private:
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

  auto iter = lopers.find(position);
  if (iter == lopers.end())
    return std::optional<Loper>();

  return iter->second;
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

  PositionSet positions(ReachablePositions<ROWS, COLUMNS>(to));

  for (const auto position : positions) {
    auto result = std::find(positions.begin(), positions.end(), position);
    if (position != from) {
      auto optionalLoper(GetLoper(position));
      if (optionalLoper && optionalLoper->colour != loper.colour)
        return false;
    }
  }

  ClearLoper(from);
  lopers[to] = loper;

  return true;
}

template <int ROWS, int COLUMNS>
inline void Board<ROWS, COLUMNS>::ClearLoper(const Position& position)
{
  auto iter = lopers.find(position);
  if (iter == lopers.end())
    throw std::runtime_error("position is empty");

  lopers.erase(iter);
}

template <int ROWS, int COLUMNS>
inline void Board<ROWS, COLUMNS>::SetLoper(const Position& position, const Loper& loper)
{
  if (lopers.find(position) != lopers.end())
    throw std::runtime_error("position is not empty");

  lopers[position] = loper;
}

template<int ROWS, int COLUMNS>
inline PositionSet Board<ROWS, COLUMNS>::OpenPositions(const Position& from) const
{
  PositionSet openPositions;
  PositionSet positions(ReachablePositions<ROWS, COLUMNS>(from));
  for (const auto& position : positions)
    if (!GetLoper(position))
      openPositions.insert(position);

  return openPositions;
}

//template<int ROWS, int COLUMNS>
//LoperMap Board<ROWS, COLUMNS>::GetLopers() const
//{
//  return lopers;
//}

template<int ROWS, int COLUMNS>
LoperMap Board<ROWS, COLUMNS>::GetLopers(Loper::Colour colour) const
{
  LoperMap map;
  for (const auto& loper : lopers)
    if (loper.second.colour == colour)
      map[loper.first] = loper.second;
  return map;
}
