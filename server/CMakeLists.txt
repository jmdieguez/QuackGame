target_sources(quack_game_server
        PRIVATE
        # .cpp files
        monitor_games.cpp
        games_manager.cpp
        gameloop.cpp
        main.cpp
        server.cpp
        acceptor.cpp
        protocol.cpp
        receiver.cpp
        sender.cpp
        session.cpp
        sessions_handler.cpp

        PUBLIC
        # .h files
        monitor_games.h
        games_manager.h
        gameloop.h
        acceptor.h
        server.h
        protocol.h
        receiver.h
        sender.h
        session.h
        sessions_handler.h
)

add_subdirectory(game/)
