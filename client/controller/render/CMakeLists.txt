target_sources(quack_game_client
    PRIVATE
    # .cpp files
    duck.cpp
    scene.cpp
    item.cpp
    projectiledrawer.cpp
    boxitem.cpp
    mapdrawer.cpp
    renderer.cpp
    renderstorage.cpp

    PUBLIC
    # .h files
    duck.h
    scene.h
    item.h
    projectiledrawer.h
    boxitem.h
    mapdrawer.h
    renderer.h 
    renderstorage.h
)