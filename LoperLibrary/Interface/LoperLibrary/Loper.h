#pragma once

namespace loper
{

enum class Colour { White, Black };

} // namespace loper

using LoperMap = std::map<Position, loper::Colour>;
