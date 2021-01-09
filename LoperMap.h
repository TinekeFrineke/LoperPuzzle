#pragma once

#include <map>
#include <optional>

#include "Loper.h"

using LoperMap = std::map<Position, std::optional<Loper>>;
struct Position { int row{}; int column{}; };
