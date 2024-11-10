target_sources(quack_game_client
    PRIVATE
    # .cpp files
    main.cpp
)

add_subdirectory(view/)
add_subdirectory(model/)
add_subdirectory(controller/)