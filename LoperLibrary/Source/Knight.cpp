
#include "Knight.h"


namespace
{
std::array<Move, 8> possibleMoves =
{
  Move({ 2, -1}),
  Move({ 1, -2}),
  Move({ 1,  2}),
  Move({ 2,  1}),
  Move({-2,  1}),
  Move({-1,  2}),
  Move({-1, -2}),
  Move({-2, -1}),
};
}

namespace knight
{
PositionSet Knight::GetPossibleTargetPositions(const Position& currentPositon) const
{
  PositionSet positions;
  if (colour == Colour::Fixed)
    return positions;

  for (const Move& move : possibleMoves)
    positions.insert(currentPositon + move);

  return positions;
}
} // namespace knight