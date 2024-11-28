target_sources(quack_game_server
    PRIVATE
    # .cpp files
    game.cpp
    hitbox.cpp

    PUBLIC
    # .h files
    hitbox.h
    game.h
    map.h
)

add_subdirectory(gun/)
add_subdirectory(duck/)
add_subdirectory(color/)
add_subdirectory(manager/)