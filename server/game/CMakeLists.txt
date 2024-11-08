target_sources(quack_game_common
    PRIVATE
    # .cpp files
    gun/cowboypistol.cpp
    game.cpp
    duck.cpp
    PUBLIC
    # .h files
    gun/gun.h
    gun/cowboypistol.h
    gun/defminvalue.h
    duck.h
    game.h
    map.h
    projectile.h
    )
