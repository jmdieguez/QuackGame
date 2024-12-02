target_sources(quack_game_client
    PRIVATE
    # .cpp files
    chunk.cpp 
    soundbox.cpp
    soundboxstorage.cpp
    projectilesound.cpp
    explosionsound.cpp
    soundmanager.cpp
    projectilelasersound.cpp

    PUBLIC
    # .h files
    chunk.h
    soundbox.h
    soundboxstorage.h
    projectilesound.h
    explosionsound.h
    soundmanager.h
    projectilelasersound.h

)