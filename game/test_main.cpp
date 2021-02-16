#include "game/Game.h"
#include <iostream>
#include <variant>

int main() {
    auto game = Game();
    for (auto& state = game.start(300); std::holds_alternative<InGameState>(state); game.turn(Throwing::ROCK)) {
        auto& inGameState = std::get<InGameState>(state);
        std::cout << inGameState.winCount << "/" << inGameState.loseCount << "/" << inGameState.drawCount << std::endl;
    }
    const auto& endGameState = std::get<EndGameState>(game.peekState());
    std::cout << "Winner: " << getLabelForGameWinner(endGameState.winner) << std::endl;
}