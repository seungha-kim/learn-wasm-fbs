#include "flatbuffers/generated/GameInput_generated.h"
#include "flatbuffers/generated/GameOutput_generated.h"
#include "game-facade/GameFacade.h"
#include "game/Game.h"
#include <iostream>

void start(Game& game, GameFacade& facade) {
    // input
    flatbuffers::FlatBufferBuilder inputBuilder { 1024 };
    auto gameStartCommand = RPS::CreateGameStartCommand(inputBuilder, 3);
    auto gameInput = RPS::CreateGameInput(inputBuilder, RPS::AnyInput_GameStartCommand, gameStartCommand.Union());
    inputBuilder.Finish(gameInput);
    facade.input(game, inputBuilder.GetBufferPointer());
}

void turn(Game& game, GameFacade& facade) {
    // input
    flatbuffers::FlatBufferBuilder inputBuilder { 1024 };
    auto turnInput = RPS::CreateTurnInput(inputBuilder, RPS::Throwing_ROCK);
    auto gameInput = RPS::CreateGameInput(inputBuilder, RPS::AnyInput_TurnInput, turnInput.Union());
    inputBuilder.Finish(gameInput);
    facade.input(game, inputBuilder.GetBufferPointer());
}

void getOutput(Game& game, GameFacade& facade) {
    // output
    uint8_t* outputBuffer;
    size_t outputBufferSize;
    facade.getPendingOutput(&outputBuffer, &outputBufferSize);
    //    std::cout << outputBufferSize << std::endl;
    flatbuffers::FlatBufferBuilder outputBuilder { 1024 };
    auto gameOutput = RPS::GetGameOutput(outputBuffer);
    std::cout << gameOutput->gameData()->winCount() << "/" << gameOutput->gameData()->loseCount() << "/"
              << gameOutput->gameData()->drawCount() << std::endl;
}

int main() {
    auto game = Game();
    auto facade = GameFacade();
    start(game, facade);
    getOutput(game, facade);
    turn(game, facade);
    getOutput(game, facade);
    turn(game, facade);
    getOutput(game, facade);
    turn(game, facade);
    getOutput(game, facade);
}