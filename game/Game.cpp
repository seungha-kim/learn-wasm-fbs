#include "Game.h"
#include <chrono>

static TurnWinner decideTurnWinner(Throwing me, Throwing opponent) {
    if (me == opponent) {
        return TurnWinner::DRAW;
    } else if ((me == Throwing::ROCK && opponent == Throwing::SCISSORS)
            || (me == Throwing::PAPER && opponent == Throwing::ROCK)
            || (me == Throwing::SCISSORS && opponent == Throwing::PAPER)) {
        return TurnWinner::ME;
    } else {
        return TurnWinner::OPPONENT;
    }
}

const AnyGameState& Game::start(unsigned int best) {
    m_generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    if (auto p = std::get_if<InGameState>(&m_state)) {
        throw std::runtime_error("Can't start again in game");
    }

    m_state = InGameState { .best = best };
    return m_state;
}

const AnyGameState& Game::stop() {
    m_state = EndGameState { .winner = GameWinner::NOT_DECIDED };
    return m_state;
}

const AnyGameState& Game::turn(Throwing throwing) {
    auto& inGameState = std::get<InGameState>(m_state);
    auto opponentThrowing = randomThrowing();
    auto winner = decideTurnWinner(throwing, opponentThrowing);
    switch (winner) {
    case TurnWinner::ME:
        inGameState.winCount += 1;
        if (inGameState.winCount >= inGameState.best) {
            m_state = EndGameState { .winner = GameWinner::ME, .lastState = inGameState };
        }
        break;
    case TurnWinner::OPPONENT:
        inGameState.loseCount += 1;
        if (inGameState.loseCount >= inGameState.best) {
            m_state = EndGameState { .winner = GameWinner::OPPONENT, .lastState = inGameState };
        }
        break;
    case TurnWinner::DRAW:
        inGameState.drawCount += 1;
        break;
    }
    return m_state;
}

Throwing Game::randomThrowing() {
    switch (m_distribution(m_generator)) {
    case 0:
        return Throwing::ROCK;
    case 1:
        return Throwing::PAPER;
    case 2:
        return Throwing::SCISSORS;
    default:
        throw std::runtime_error("impossible");
    }
}

const AnyGameState& Game::peekState() const {
    return m_state;
}
