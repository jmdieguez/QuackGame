target_sources(quack_game_client
    PRIVATE
    # .cpp files
    SDLWindow.cpp
    main_window.ui
    create_room.ui
    main_window.cpp
        create_room.cpp


    PUBLIC
    # .h files
    SDLWindow.h
    main_window.h
    create_room.h
)
