#pragma once

#include <optional>
#include <set>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

#include "Position.h"

template <int ROWS, int COLUMNS>
bool IsValid(const Position& position)
{
  return position.row >= 0 && position.row < ROWS&& position.column >= 0 && position.column < COLUMNS;
}

template <typename PIECE, int ROWS, int COLUMNS>
class Board
{
public:
  using PieceMap = std::map<Position, PIECE>;

  Board();
  virtual ~Board() {}

  virtual bool IsThreatened(const Position& position, const PIECE& piece) const = 0;
  virtual bool Place(const PIECE& piece, const Position& from, const Position& to) = 0;
  virtual PositionSet ReachablePositions(const Position& position, const PIECE& piece) const = 0;

  bool IsFree(const Position& position) const { return pieces.find(position) == pieces.end(); }
  std::optional<PIECE> GetPiece(const Position& position) const;
  void Clear(const Position& position);
  void SetPiece(const Position& position, PIECE piece);
  void Clear() { pieces.clear(); }
  void AssertValid(const Position& position);

  PieceMap GetPieces() const;

  bool operator<(const Board<PIECE, ROWS, COLUMNS>& rhs) const { return pieces < rhs.pieces; }
  bool operator==(const Board<PIECE, ROWS, COLUMNS>& rhs) const { return pieces == rhs.pieces; }
  bool Equals(const Board<PIECE, ROWS, COLUMNS>& rhs) const { return pieces == rhs.pieces; }

protected:
  PieceMap& GetPiecesReference() { return pieces; }

private:
  PieceMap pieces;
};

template <typename PIECE, int ROWS, int COLUMNS>
inline Board<PIECE, ROWS, COLUMNS>::Board()
{
}

template <typename PIECE, int ROWS, int COLUMNS>
inline std::optional<PIECE> Board<PIECE, ROWS, COLUMNS>::GetPiece(const Position& position) const
{
  if (!IsValid<ROWS, COLUMNS>(position))
    throw std::runtime_error("row or clum out of range");

  auto iter = pieces.find(position);
  if (iter == pieces.end())
    return std::optional<PIECE>();

  return iter->second;
}

template <typename PIECE, int ROWS, int COLUMNS>
inline void Board<PIECE, ROWS, COLUMNS>::Clear(const Position& position)
{
  auto iter = pieces.find(position);
  if (iter == pieces.end())
    throw std::runtime_error("position is empty");

  pieces.erase(iter);
}

template <typename PIECE, int ROWS, int COLUMNS>
inline void Board<PIECE, ROWS, COLUMNS>::SetPiece(const Position& position, PIECE piece)
{
  if (pieces.find(position) != pieces.end())
    throw std::runtime_error("position is not empty");

  pieces[position] = piece;
}

template<typename PIECE, int ROWS, int COLUMNS>
inline void Board<PIECE, ROWS, COLUMNS>::AssertValid(const Position& position)
{
  if (!IsValid<ROWS, COLUMNS>(position))
    throw std::runtime_error("row or column out of range");
}

template<typename PIECE, int ROWS, int COLUMNS>
typename Board<PIECE, ROWS, COLUMNS>::PieceMap Board<PIECE, ROWS, COLUMNS>::GetPieces() const
{
  return pieces;
}
