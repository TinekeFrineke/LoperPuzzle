
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

PositionSet Knight::GetPossibleTargetPositions(const Position& currentPositon)
{
  PositionSet positions;
  for (const Move& move : possibleMoves)
    positions.insert(currentPositon + move);

  return positions;
}
