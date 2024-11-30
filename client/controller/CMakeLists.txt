target_sources(quack_game_client
    PRIVATE
    # .cpp files
    game.cpp
        launcher.cpp

    PUBLIC
    # .h files
    game.h
        launcher.h
)
add_subdirectory(session/)
add_subdirectory(music/)
add_subdirectory(render/)