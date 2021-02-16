add_library(game Game.cpp Game.h Throwing.h Throwing.cpp GameWinner.cpp GameWinner.h)

add_executable(test-game test_main.cpp)
target_link_libraries(test-game game)