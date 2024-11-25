target_sources(quack_game_server
        PRIVATE
        # .cpp files
        monitor_games.cpp
        gameloop.cpp
        main.cpp
        server.cpp
        acceptor.cpp
        protocol.cpp
        receiver.cpp
        sender.cpp
        session.cpp
        sessions_handler.cpp
        lobby_session.cpp
        
        PUBLIC
        # .h files
        monitor_games.h
        gameloop.h
        acceptor.h
        server.h
        protocol.h
        receiver.h
        sender.h
        session.h
        sessions_handler.h
        lobby_session.h
)

add_subdirectory(game/)