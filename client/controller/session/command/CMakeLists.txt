target_sources(quack_game_client
    PRIVATE
    # .cpp files
    gamecontext.cpp
    inputhandler.cpp
    playerkeyconfig.cpp
    playerkeyconfigmanager.cpp
    movebentdown.cpp
    moveleft.cpp
    moveright.cpp
    shoot.cpp
    drop.cpp
    grab.cpp
    jump.cpp
    lookingup.cpp

    PUBLIC
    # .h files
    gamecontext.h
    command.h
    inputhandler.h
    playerkeyconfig.h
    playerkeyconfigmanager.h
    movebentdown.h
    moveleft.h
    moveright.h
    shoot.h
    drop.h
    grab.h
    jump.h
    lookingup.h

)
