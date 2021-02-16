#include "GameFacade.h"
#include "GameInput_generated.h"
#include "GameOutput_generated.h"

static flatbuffers::Offset<RPS::GameData> createGameDataFromState(
        flatbuffers::FlatBufferBuilder& builder, InGameState& state) {
    auto turnCount = state.loseCount + state.drawCount + state.winCount;
    return RPS::CreateGameData(builder, turnCount, state.winCount, state.drawCount, state.loseCount);
}

void GameFacade::input(Game& game, uint8_t* buffer) {
    auto gameInput = RPS::GetGameInput(buffer);
    switch (gameInput->anyInput_type()) {
    case RPS::AnyInput_GameStartCommand:
        handleGameStartCommand(game, gameInput->anyInput_as_GameStartCommand());
        break;
    case RPS::AnyInput_GameStopCommand:
        handleGameStopCommand(game, gameInput->anyInput_as_GameStopCommand());
        break;
    case RPS::AnyInput_TurnInput:
        handleTurnInput(game, gameInput->anyInput_as_TurnInput());
        break;
    case RPS::AnyInput_NONE:
        break;
    }
}

void GameFacade::getPendingOutput(uint8_t** buffer, size_t* size) {
    if (m_pendingOutputs.empty()) {
        *size = 0;
    } else {
        flatbuffers::FlatBufferBuilder builder { 1024 };
        auto lastState = m_pendingOutputs.front();
        m_pendingOutputs.erase(m_pendingOutputs.begin());
        if (auto preGameState = std::get_if<PreGameState>(&lastState)) {
            *size = 0;
        } else if (auto inGameState = std::get_if<InGameState>(&lastState)) {
            auto gameData = createGameDataFromState(builder, *inGameState);
            auto gameOutput = RPS::CreateGameOutput(builder, RPS::GameEvent_IN_GAME, 0, gameData);
            builder.Finish(gameOutput);
            *buffer = builder.GetBufferPointer();
            *size = builder.GetSize();
        } else if (auto endGameState = std::get_if<EndGameState>(&lastState)) {
            auto gameData = createGameDataFromState(builder, endGameState->lastState);
            auto gameOutput = RPS::CreateGameOutput(builder, RPS::GameEvent_FINISHED, 0, gameData);
            builder.Finish(gameOutput);
            *buffer = builder.GetBufferPointer();
            *size = builder.GetSize();
        }
    }
}

void GameFacade::handleGameStartCommand(Game& game, const RPS::GameStartCommand* command) {
    game.start(command->best());
    m_pendingOutputs.push_back(game.peekState());
}

void GameFacade::handleGameStopCommand(Game& game, const RPS::GameStopCommand* command) {
    game.stop();
    m_pendingOutputs.push_back(game.peekState());
}

void GameFacade::handleTurnInput(Game& game, const RPS::TurnInput* input) {
    auto throwing = convertThrowingFromWire(input->throwing());
    game.turn(throwing);
    m_pendingOutputs.push_back(game.peekState());
}
