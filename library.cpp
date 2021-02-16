#include "library.h"

//------------------------------
// MARK:- Public Game class

Game::Game() {
    m_impl = new GameImpl;
}

Game::~Game() {
    delete m_impl;
}

void Game::input(unsigned char* inputPtr) {
    // TODO: pending output 있는데 input 이 먼저 들어오면 error
    auto input = RPS::GetGameInput(inputPtr);
    switch (input->anyInput_type()) {
    case RPS::AnyInput_GameStartCommand:
        m_impl->start(input->anyInput_as_GameStartCommand()->best());
        break;
    case RPS::AnyInput_GameStopCommand:
        m_impl->stop();
        break;
    case RPS::AnyInput_TurnInput:
        m_impl->turn(convertThrowingFromWire(input->anyInput_as_TurnInput()->throwing()));
        break;
    default:
        break;
    }
}

void Game::getPendingOutput(unsigned char* output, size_t* size) { }
