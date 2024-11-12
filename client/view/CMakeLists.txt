target_sources(quack_game_client
    PRIVATE
    # .cpp files
    SDLWindow.cpp
    main_window.ui
    create_room.ui
    main_window.cpp
    lobby.cpp

    PUBLIC
    # .h files
    SDLWindow.h
    main_window.h
    lobby.h
)
