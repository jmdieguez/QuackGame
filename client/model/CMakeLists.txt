target_sources(quack_game_client
    PRIVATE
    # .cpp files
    protocol.cpp
    receiver.cpp
    sender.cpp

    PUBLIC
    # .h files
    protocol.h
    receiver.h
    sender.h
)

add_subdirectory(resource/)
add_subdirectory(lobby/)