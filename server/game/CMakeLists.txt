target_sources(quack_game_server
    PRIVATE
    # .cpp files
    game.cpp
    duck.cpp
    PUBLIC
    # .h files
    duck.h
    game.h
    map.h
)

add_subdirectory(gun/)