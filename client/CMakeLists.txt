target_sources(quack_game_client
    PRIVATE
    # .cpp files
    controller/game.cpp
    model/network.cpp
    model/protocol.cpp
    main.cpp
    PUBLIC
    # .h files
    controller/game.h 
    model/network.h
    model/protocol.h
    )
