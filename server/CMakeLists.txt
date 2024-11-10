target_sources(quack_game_server
    PRIVATE
    # .cpp files
        gameloop.cpp
        main.cpp
        server.cpp
        games_manager.cpp
        acceptor.cpp
        protocol.cpp
        receiver.cpp
        sender.cpp
        session.cpp
        sessions_handler.cpp

    PUBLIC
    # .h files
        gameloop.h
        games_manager.h
        acceptor.h
        server.h
        protocol.h
        receiver.h
        sender.h
        server.h
        session.h
        sessions_handler.h
    )

add_subdirectory(game/)