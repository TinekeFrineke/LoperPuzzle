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
class Board
{
public:
  Board();

  bool IsThreatened(const Position& position, loper::Colour loper) const;
  bool IsFree(const Position& position) const { return lopers.find(position) == lopers.end(); }
  std::optional<loper::Colour> GetLoper(const Position& position) const;
  bool PlaceLoper(loper::Colour loper, const Position& from, const Position& to);
  void ClearLoper(const Position& position);
  void SetLoper(const Position& position, loper::Colour loper);
  PositionSet ReachablePositions(const Position& position, loper::Colour loper) const;
  void Clear() { lopers.clear(); }

  LoperMap GetLopers() const;

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
inline std::optional<loper::Colour> Board<ROWS, COLUMNS>::GetLoper(const Position& position) const
{
  if (!IsValid<ROWS, COLUMNS>(position))
    throw std::runtime_error("row or clum out of range");

  auto iter = lopers.find(position);
  if (iter == lopers.end())
    return std::optional<loper::Colour>();

  return iter->second;
}

template <int ROWS, int COLUMNS>
inline bool Board<ROWS, COLUMNS>::PlaceLoper(loper::Colour loper, const Position& from, const Position& to)
{
  if (!IsValid<ROWS, COLUMNS>(from))
    throw std::runtime_error("from: row or clum out of range");
  if (!IsValid<ROWS, COLUMNS>(to))
    throw std::runtime_error("from: row or clum out of range");

  std::optional<loper::Colour> loperFrom = GetLoper(from);
  if (!loperFrom)
    throw std::runtime_error("loper not found");

  std::optional<loper::Colour> loperTo = GetLoper(to);
  if (loperTo)
    return false;

  PositionSet positions(ReachablePositions(to, *loperFrom));

  if (IsThreatened(to, *loperFrom))
    return false;

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
inline void Board<ROWS, COLUMNS>::SetLoper(const Position& position, loper::Colour loper)
{
  if (lopers.find(position) != lopers.end())
    throw std::runtime_error("position is not empty");

  lopers[position] = loper;
}

template <int ROWS, int COLUMNS>
inline bool Board<ROWS, COLUMNS>::IsThreatened(const Position& position, loper::Colour loper) const
{
  for (const auto& otherLoper : lopers) {
    if (otherLoper.second == loper)
      continue;

    PositionSet otherPositions(ReachablePositions(otherLoper.first, otherLoper.second));
    if (otherPositions.find(position) != otherPositions.end())
      return true;
  }

  return false;
}

template <int ROWS, int COLUMNS>
inline PositionSet Board<ROWS, COLUMNS>::ReachablePositions(const Position& position, loper::Colour loper) const
{
  PositionSet positions;
  if (ROWS < COLUMNS) {
    for (int row = position.row - 1; row >= 0; --row) {
      Position toAdd({ row, position.column + position.row - row });
      if (!IsValid<ROWS, COLUMNS>(toAdd) || !IsFree(toAdd))
        break;

      positions.insert(toAdd);
    }
    for (int row = position.row - 1; row >= 0; --row) {
      Position toAdd({ row, position.column - position.row + row });
      if (!IsValid<ROWS, COLUMNS>(toAdd) || !IsFree(toAdd))
        break;

      positions.insert(toAdd);
    }
    for (int row = position.row + 1; row < ROWS; ++row) {
      Position toAdd({ row, position.column + position.row - row });
      if (!IsValid<ROWS, COLUMNS>(toAdd) || !IsFree(toAdd))
        break;

      positions.insert(toAdd);
    }
    for (int row = position.row + 1; row < ROWS; ++row) {
      Position toAdd({ row, position.column - position.row + row });
      if (!IsValid<ROWS, COLUMNS>(toAdd) || !IsFree(toAdd))
        break;
        
      std::optional<loper::Colour> otherloper(GetLoper(toAdd));
      if (otherloper && *otherloper != loper)
        break;

      positions.insert(toAdd);
    }
  }
  else {
    for (int column = position.column - 1; column >= 0; --column) {
      Position toAdd({ position.row + position.column - column, column });
      if (!IsValid<ROWS, COLUMNS>(toAdd) || !IsFree(toAdd))
        break;

      positions.insert(toAdd);
    }

    for (int column = position.column - 1; column >= 0; --column) {
      Position toAdd({ position.row - position.column + column, column });
      if (!IsValid<ROWS, COLUMNS>(toAdd) || !IsFree(toAdd))
        break;

      positions.insert(toAdd);
    }

    for (int column = position.column + 1; column < COLUMNS; ++column) {
      Position toAdd({ position.row + position.column - column, column });
      if (!IsValid<ROWS, COLUMNS>(toAdd) || !IsFree(toAdd))
        break;

      positions.insert(toAdd);
    }

    for (int column = position.column + 1; column < COLUMNS; ++column) {
      Position toAdd({ position.row - position.column + column, column });
      if (!IsValid<ROWS, COLUMNS>(toAdd) || !IsFree(toAdd))
        break;

      positions.insert(toAdd);
    }
  }

  return positions;
}

template<int ROWS, int COLUMNS>
LoperMap Board<ROWS, COLUMNS>::GetLopers() const
{
  return lopers;
}
