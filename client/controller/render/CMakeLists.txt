target_sources(quack_game_client
    PRIVATE
    # .cpp files
    duck.cpp
    scene.cpp
    renderer.cpp
    renderstorage.cpp

    PUBLIC
    # .h files
    duck.h
    scene.h
    renderer.h 
    renderstorage.h
)