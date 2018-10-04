#pragma once

#include "direction.h"

class Randomizer
{
  private:
    Randomizer() {}
    static void Initialize();

  public:
    static Direction Orientation();
    static int Position(int length);
};