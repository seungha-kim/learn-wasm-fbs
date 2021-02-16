#ifndef LEARN_WASM_FBS_LIBRARY_H
#define LEARN_WASM_FBS_LIBRARY_H

#include "GameInput_generated.h"
#include "GameOutput_generated.h"

class GameImpl;

class Game final {
    Game();
    ~Game();
    void input(unsigned char* input);
    void getPendingOutput(unsigned char* output, size_t* size);

private:
    GameImpl* m_impl;
};

#endif // LEARN_WASM_FBS_LIBRARY_H
