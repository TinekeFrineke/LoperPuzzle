#pragma once

#include <map>
#include <set>
#include <optional>

class PuzzleException {};
struct Position { int row{}; int column{}; };
struct Move { int rows{}; int columns{}; };
inline bool operator==(const Position& a, const Position& b) { return a.row == b.row && a.column == b.column; }
inline bool operator!=(const Position& a, const Position& b) { return !(a == b); }
inline bool operator<(const Position& a, const Position& b) { return a.row < b.row || (a.row == b.row && a.column < b.column); }

inline Position operator+(const Position& position, const Move move)
{
  return Position({ position.row + move.rows, position.column + move.columns });
}

using PositionSet = std::set<Position>;
