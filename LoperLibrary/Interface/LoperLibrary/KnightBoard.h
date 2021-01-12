#pragma once

#include "Board.h"
#include "Knight.h"

template <int ROWS, int COLUMNS>
class KnightBoard : public Board<Knight, ROWS, COLUMNS> {
public:
  bool Place(const Knight& knight, const Position& from, const Position& to);
  PositionSet ReachablePositions(const Position& position, const Knight& knight) const;

  using Board<Knight, ROWS, COLUMNS>::GetPiece;
  using Board<Knight, ROWS, COLUMNS>::IsFree;
};

template <int ROWS, int COLUMNS>
inline bool KnightBoard<ROWS, COLUMNS>::Place(const Knight& knight, const Position& from, const Position& to) {
  if (!IsValid<ROWS, COLUMNS>(from))
    throw std::runtime_error("from: row or clum out of range");
  if (!IsValid<ROWS, COLUMNS>(to))
    throw std::runtime_error("from: row or clum out of range");

  if (IsFree(from))
    throw std::runtime_error("knight not found");

  if (!IsFree(to))
    return false;

  Board<Knight, ROWS, COLUMNS>::Clear(from);
  Board<Knight, ROWS, COLUMNS>::GetPiecesReference()[to] = knight;

  return true;
}

template <int ROWS, int COLUMNS>
inline PositionSet KnightBoard<ROWS, COLUMNS>::ReachablePositions(const Position& position, const Knight& knight) const {
  PositionSet positions(knight.GetPossibleTargetPositions());
  PositionSet reachablePositions;
  for (const auto& position : positions)
    if (IsValid(position) && IsFree(position))
      reachablePositions.insert(position);

  return reachablePositions;
}
