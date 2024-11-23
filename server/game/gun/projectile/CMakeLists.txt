target_sources(quack_game_server
    PRIVATE
    # .cpp files
    projectilegrenade.cpp
    projectilegun.cpp
    projectilebanana.cpp

    PUBLIC
    # .h files
    projectile.h
    projectilegrenade.h
    projectilebanana.h
    projectilegun.h
)
