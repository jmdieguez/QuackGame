target_sources(quack_game_server
    PRIVATE
    # .cpp files
    dispersionlow.cpp
    dispersionmedium.cpp
    dispersionhigh.cpp
    dispersiongrenade.cpp

    PUBLIC
    # .h files
    dispersionlow.h
    dispersionmedium.h
    dispersionhigh.h
    dispersiongrenade.h
    dispersion.h
)