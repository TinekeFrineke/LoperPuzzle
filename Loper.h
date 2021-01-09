#pragma once
class Loper
{
public:
  enum class Colour { White, Black };

  Loper(Colour aColour) : colour(aColour) {}
  Loper(const Loper& loper) : colour(loper.colour) {}

  static Loper WhiteLoper() { return Loper(Colour::White); }
  static Loper BlackLoper() { return Loper(Colour::Black); }

  Colour colour;
};

