target_sources(quack_game_server
    PRIVATE
    # .cpp files
    guncontroller.cpp
    movecontroller.cpp
    duck.cpp

    PUBLIC
    # .h files
    guncontroller.h
    movecontroller.h
    duck.h
)
