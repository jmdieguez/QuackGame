target_sources(quack_game_tests
    PRIVATE
    # .cpp files
   testProtocolServer.cpp
    PUBLIC
    # .h files
    )

add_subdirectory(mock/)
