target_sources(quack_game_client
    PRIVATE
    # .cpp files
    gamecontext.cpp
    inputhandler.cpp
    movebentdown.cpp
    moveleft.cpp
    moveright.cpp
    shoot.cpp
    drop.cpp
    grab.cpp

    PUBLIC
    # .h files
    gamecontext.h
    command.h
    inputhandler.h
    movebentdown.h
    moveleft.h
    moveright.h
    shoot.h
    drop.h
    grab.cpp
)
