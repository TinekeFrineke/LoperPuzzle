#pragma once

#include "Board.h"
#include "Loper.h"


template <int ROWS, int COLUMNS>
class LoperBoard : public Board<loper::Colour, ROWS, COLUMNS>
{
public:
  bool Place(const loper::Colour& loper, const Position& from, const Position& to) override;
  PositionSet ReachablePositions(const Position& position, const loper::Colour& loper) const override;

  bool IsThreatened(const Position& position, const loper::Colour& loper) const;

  using Board<loper::Colour, ROWS, COLUMNS>::GetPiece;
  using Board<loper::Colour, ROWS, COLUMNS>::IsFree;
};

template <int ROWS, int COLUMNS>
inline bool LoperBoard<ROWS, COLUMNS>::IsThreatened(const Position& position, const loper::Colour& loper) const
{
  for (const auto& otherLoper : Board<loper::Colour, ROWS, COLUMNS>::GetPieces()) {
    if (otherLoper.second == loper)
      continue;

    PositionSet otherPositions(ReachablePositions(otherLoper.first, otherLoper.second));
    if (otherPositions.find(position) != otherPositions.end())
      return true;
  }

  return false;
}

template <int ROWS, int COLUMNS>
inline bool LoperBoard<ROWS, COLUMNS>::Place(const loper::Colour& loper, const Position& from, const Position& to)
{
  if (!IsValid<ROWS, COLUMNS>(from))
    throw std::runtime_error("from: invalid position");
  if (!IsValid<ROWS, COLUMNS>(to))
    throw std::runtime_error("to: invalid position");

  std::optional<loper::Colour> loperFrom = Board<loper::Colour, ROWS, COLUMNS>::GetPiece(from);
  if (!loperFrom)
    throw std::runtime_error("loper not found");

  std::optional<loper::Colour> loperTo = Board<loper::Colour, ROWS, COLUMNS>::GetPiece(to);
  if (loperTo)
    return false;

  PositionSet positions(ReachablePositions(to, *loperFrom));

  if (IsThreatened(to, *loperFrom))
    return false;

  Board<loper::Colour, ROWS, COLUMNS>::Clear(from);
  Board<loper::Colour, ROWS, COLUMNS>::GetPiecesReference()[to] = loper;

  return true;
}

template <int ROWS, int COLUMNS>
inline PositionSet LoperBoard<ROWS, COLUMNS>::ReachablePositions(const Position& position, const loper::Colour& loper) const
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

      std::optional<loper::Colour> otherloper(GetPiece(toAdd));
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

