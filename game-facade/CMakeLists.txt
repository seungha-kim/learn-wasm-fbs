add_library(game-facade GameFacade.cpp GameFacade.h)

add_executable(test-game-facade test-game-facade.cpp test-game-facade.cpp)
target_link_libraries(test-game-facade game game-facade)