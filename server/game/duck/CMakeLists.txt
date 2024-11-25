target_sources(quack_game_server
    PRIVATE
    # .cpp files
    duck.cpp
    guncontroller.cpp
    movecontroller.cpp

    PUBLIC
    # .h files
    duck.h
    guncontroller.h
    movecontroller.h
    defs.h
)
