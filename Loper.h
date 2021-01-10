#pragma once
class Loper
{
public:
  enum class Colour { White, Black };

  Loper() : colour() {}
  Loper(Colour aColour) : colour(aColour) {}
  Loper(const Loper& loper) : colour(loper.colour) {}

  bool operator==(const Loper& rhs) const { return colour == rhs.colour; }
  bool operator<(const Loper& rhs) const { return colour < rhs.colour; }

  static Loper WhiteLoper() { return Loper(Colour::White); }
  static Loper BlackLoper() { return Loper(Colour::Black); }

  Colour colour{ Colour::White };
};

