target_sources(quack_game_client
    PRIVATE
    # .cpp files
    sessioncontroller.cpp

    PUBLIC
    # .h files
    sessioncontroller.h 
)

add_subdirectory(command/)
add_subdirectory(cheat/)