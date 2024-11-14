target_sources(quack_game_server
    PRIVATE
    # .cpp files
    game.cpp
    duck.cpp
    hitbox.cpp

    PUBLIC
    # .h files
    duck.h
    hitbox.h
    game.h
    map.h
)

add_subdirectory(gun/)