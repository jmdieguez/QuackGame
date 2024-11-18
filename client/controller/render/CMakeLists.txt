target_sources(quack_game_client
    PRIVATE
    # .cpp files
    duck.cpp
    scene.cpp
    item.cpp
    boxitem.cpp
    renderer.cpp
    renderstorage.cpp

    PUBLIC
    # .h files
    duck.h
    scene.h
    item.h
    boxitem.h
    renderer.h 
    renderstorage.h
)