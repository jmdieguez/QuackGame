target_sources(quack_game_client
    PRIVATE
    # .cpp files
    chunk.cpp 
    musicbox.cpp
    musicboxstorage.cpp
    projectilesound.cpp
    explosionsound.cpp

    PUBLIC
    # .h files
    chunk.h
    musicbox.h
    musicboxstorage.h
    projectilesound.h
    explosionsound.h

)