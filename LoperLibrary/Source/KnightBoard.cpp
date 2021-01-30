
#include "KnightBoard.h"

namespace knight
{
bool Move::operator==(const Move& move) const
{
  return knight == move.knight && from == move.from && to == move.to;
}
} // namespace knight