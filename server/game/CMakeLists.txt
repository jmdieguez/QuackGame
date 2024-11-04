target_sources(quack_game_common
    PRIVATE
    # .cpp files
    gun/cowboyweapon.cpp
    game.cpp
    duck.cpp
    PUBLIC
    # .h files
    gun/gun.h
    gun/cowboyweapon.h
    duck.h
    game.h
    map.h
    shoot_event.h
    )
