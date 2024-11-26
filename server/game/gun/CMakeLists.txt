target_sources(quack_game_server
    PRIVATE
    # .cpp files
    cowboypistol.cpp
    magnum.cpp
    duelingpistol.cpp
    shotgun.cpp
    sniper.cpp
    ak.cpp
    pewpewlaser.cpp
    grenade.cpp
    banana.cpp
    positiongun.cpp
    laserrifle.cpp

    PUBLIC
    # .h files
    gun.h
    cowboypistol.h
    magnum.h
    duelingpistol.h
    shotgun.h
    sniper.h
    ak.h
    pewpewlaser.h
    grenade.h
    defminvalue.h
    moveback.h
    gunammo.h
    banana.cpp
    positiongun.h
    laserrifle.h
)

add_subdirectory(projectile/)
add_subdirectory(dispersion/)
