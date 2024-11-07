target_sources(quack_game_server
    PRIVATE
    # .cpp files
    gameloop.cpp
    main.cpp
    server.cpp
    acceptor.cpp
    protocol.cpp
    receiver.cpp
    sender.cpp
    session.cpp
    sessions_handler.cpp
    games_manager.cpp
    
    PUBLIC
    # .h files
    gameloop.h
    acceptor.h
    server.h
    protocol.h
    receiver.h
    sender.h
    server.h
    session.h
    sessions_handler.h
    games_manager.h
    )

add_subdirectory(game/)