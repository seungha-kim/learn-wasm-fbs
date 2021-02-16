#pragma once

#include "GameInput_generated.h"
#include "GameOutput_generated.h"
#include "game/Game.h"
#include <vector>

class GameFacade final {
public:
    void input(Game& game, uint8_t* buffer);
    void getPendingOutput(uint8_t** buffer, size_t* size);

private:
    void handleGameStartCommand(Game& game, const RPS::GameStartCommand* command);
    void handleGameStopCommand(Game& game, const RPS::GameStopCommand* command);
    void handleTurnInput(Game& game, const RPS::TurnInput* command);
    std::vector<AnyGameState> m_pendingOutputs;
};
