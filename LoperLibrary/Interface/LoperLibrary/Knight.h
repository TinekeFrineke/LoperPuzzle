#pragma once

#include <array>

#include "Position.h"

namespace knight
{
// Fixed means: not really part of the board. Use it to
// create an irregular board
enum class Colour { White, Black, Fixed };

class Knight {
public:
  Knight() : colour(Colour::Fixed) {}
  explicit Knight(Colour _colour) : colour(_colour) {}
  Colour GetColour() const { return colour; }

  Knight& operator=(const Knight& knight) { colour = knight.colour; return* this; }
  bool operator==(const Knight& knight) const { return colour == knight.colour; }
  bool operator<(const Knight& knight) const { return colour < knight.colour; }

  PositionSet GetPossibleTargetPositions(const Position& currentPositon) const;

private:
  Colour colour;
};

using KnightMap = std::map<Position, Knight>;

} // namespace knight