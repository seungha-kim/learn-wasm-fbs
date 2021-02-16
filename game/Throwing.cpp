#include "Throwing.h"

Throwing convertThrowingFromWire(RPS::Throwing throwing) {
    switch (throwing) {
    case RPS::Throwing_ROCK:
        return Throwing::ROCK;
    case RPS::Throwing_PAPER:
        return Throwing::PAPER;
    case RPS::Throwing_SCISSORS:
        return Throwing::SCISSORS;
    default:
        return Throwing::ROCK;
    }
}

RPS::Throwing convertThrowingToWire(Throwing throwing) {
    switch (throwing) {
    case Throwing::ROCK:
        return RPS::Throwing_ROCK;
    case Throwing::PAPER:
        return RPS::Throwing_PAPER;
    case Throwing::SCISSORS:
        return RPS::Throwing_SCISSORS;
    }
}
