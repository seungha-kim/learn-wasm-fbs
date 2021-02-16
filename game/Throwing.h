#pragma once

#include "Types_generated.h"

enum class Throwing {
    ROCK,
    PAPER,
    SCISSORS,
};

Throwing convertThrowingFromWire(RPS::Throwing throwing);
RPS::Throwing convertThrowingToWire(Throwing throwing);
