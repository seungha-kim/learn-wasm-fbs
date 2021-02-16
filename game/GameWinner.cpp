#include "GameWinner.h"

std::string getLabelForGameWinner(const GameWinner& winner) {
    switch (winner) {
    case GameWinner::ME:
        return "ME";
    case GameWinner::OPPONENT:
        return "OPPONENT";
    case GameWinner::NOT_DECIDED:
        return "NOT_DECIDED";
    }
}
