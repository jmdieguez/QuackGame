target_sources(quack_game_client
    PRIVATE
    # .cpp files
    controller/command/gamecontext.cpp
    controller/game.cpp
    controller/command/inputhandler.cpp
    controller/command/movebentdowncommand.cpp
    controller/command/moveleftcommand.cpp
    controller/command/moverightcommand.cpp
    model/network.cpp
    model/protocol.cpp
    model/receiver.cpp
    model/sender.cpp
    main.cpp
    PUBLIC
    # .h files
    controller/command/gamecontext.h
    controller/game.h 
    controller/command/command.h
    controller/command/inputhandler.h
    controller/command/movebentdowncommand.h
    controller/command/moveleftcommand.h
    controller/command/moverightcommand.h
    model/network.h
    model/protocol.h
    model/receiver.h
    model/sender.h
    )
