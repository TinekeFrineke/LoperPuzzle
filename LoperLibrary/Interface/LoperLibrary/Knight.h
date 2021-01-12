#pragma once

#include <array>

#include "Position.h"

class Knight {
public:
  // Fixed means: not really part of the board. Use it to
  // create an irregular board
  enum class Colour { White, Black, Fixed };

  static PositionSet GetPossibleTargetPositions(const Position& currentPositon);

private:
  Colour colour;
};