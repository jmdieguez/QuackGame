target_sources(quack_game_client
    PRIVATE
    # .cpp files
    SDLInitializer.cpp
    main_window.ui
    create_room.ui
    game_list.ui
    main_window.cpp
    create_room.cpp
    game_list.cpp
    start_game.cpp

    PUBLIC
    # .h files
    SDLInitializer.h
    create_room.h
    main_window.h
    game_list.h
    loading_screen.h
    start_game.h
)
