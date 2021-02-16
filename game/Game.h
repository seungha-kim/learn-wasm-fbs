#pragma once

#include "GameInput_generated.h"
#include "GameOutput_generated.h"
#include "GameWinner.h"
#include "Throwing.h"
#include "util/NonCopyable.h"
#include <iostream>
#include <random>
#include <stdexcept>
#include <variant>
#include <vector>

enum class TurnWinner {
    ME,
    OPPONENT,
    DRAW,
};

struct PreGameState { };

struct InGameState {
    unsigned best = 3;
    unsigned winCount = 0;
    unsigned drawCount = 0;
    unsigned loseCount = 0;
};

struct EndGameState {
    GameWinner winner;
    InGameState lastState;
};

using AnyGameState = std::variant<PreGameState, EndGameState, InGameState>;

class Game {
public:
    const AnyGameState& start(unsigned best);

    const AnyGameState& stop();

    const AnyGameState& turn(Throwing throwing);

    [[nodiscard]] const AnyGameState& peekState() const;

private:
    AnyGameState m_state;
    std::default_random_engine m_generator;
    std::uniform_int_distribution<int> m_distribution { 0, 2 };

    Throwing randomThrowing();
};
