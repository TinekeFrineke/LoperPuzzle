#pragma once

#include "Board.h"
#include "Knight.h"


template <int ROWS, int COLUMNS>
class KnightBoard : public Board<Knight, ROWS, COLUMNS> {
public:
  bool IsThreatened(const Position& position, const Knight& piece) const override;
  bool Place(const Knight& knight, const Position& from, const Position& to) override;
  PositionSet ReachablePositions(const Position& position, const Knight& knight) const override;

  using Parent = Board<Knight, ROWS, COLUMNS>;
};

template<int ROWS, int COLUMNS>
inline bool KnightBoard<ROWS, COLUMNS>::IsThreatened(const Position& position, const Knight& piece) const {
  return false;
}

template <int ROWS, int COLUMNS>
inline bool KnightBoard<ROWS, COLUMNS>::Place(const Knight& knight, const Position& from, const Position& to) {
  Parent::AssertValid(from);
  Parent::AssertValid(to);

  if (Parent::IsFree(from))
    throw std::runtime_error("knight not found");

  if (!Parent::IsFree(to))
    return false;

  Parent::Clear(from);
  Parent::GetPiecesReference()[to] = knight;

  return true;
}

template <int ROWS, int COLUMNS>
inline PositionSet KnightBoard<ROWS, COLUMNS>::ReachablePositions(const Position& position, const Knight& knight) const {
  PositionSet positions(knight.GetPossibleTargetPositions());
  PositionSet reachablePositions;
  for (const auto& position : positions)
    if (IsValid<ROWS, COLUMNS>(position) && Parent::IsFree(position))
      reachablePositions.insert(position);

  return reachablePositions;
}
