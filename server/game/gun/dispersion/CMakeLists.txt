target_sources(quack_game_server
    PRIVATE
    # .cpp files
    dispersionlow.cpp
    dispersionmedium.cpp
    dispersionhigh.cpp

    PUBLIC
    # .h files
    dispersionlow.h
    dispersionmedium.h
    dispersionhigh.h
    dispersion.h
)