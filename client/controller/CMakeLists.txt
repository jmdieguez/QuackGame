target_sources(quack_game_client
    PRIVATE
    # .cpp files
    game.cpp


    PUBLIC
    # .h files
    game.h 
)

add_subdirectory(command/)