target_sources(quack_game_client
    PRIVATE
    # .cpp files
    SDLWindow.cpp
    main_window.ui
    create_room.ui
    game_list.ui
    main_window.cpp
    create_room.cpp
    game_list.cpp


    PUBLIC
    # .h files
    SDLWindow.h
    main_window.h
    create_room.h
    game_list.h
)
