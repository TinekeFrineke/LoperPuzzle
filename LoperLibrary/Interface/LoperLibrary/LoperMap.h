#pragma once

#include <map>
#include <optional>

#include "Loper.h"

class PuzzleException {};
struct Position { int row{}; int column{}; };
inline bool operator==(const Position& a, const Position& b) { return a.row == b.row && a.column == b.column; }
inline bool operator!=(const Position& a, const Position& b) { return !(a == b); }
inline bool operator<(const Position& a, const Position& b) { return a.row < b.row || (a.row == b.row && a.column < b.column); }
using LoperMap = std::map<Position, loper::Colour>;
