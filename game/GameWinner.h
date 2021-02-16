#pragma once

#include <string>

enum class GameWinner {
    ME,
    OPPONENT,
    NOT_DECIDED,
};

std::string getLabelForGameWinner(const GameWinner& winner);