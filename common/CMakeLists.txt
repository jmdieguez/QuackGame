target_sources(quack_game_common
    PRIVATE
    # .cpp files
    constant_rate_loop.cpp
    liberror.cpp
    resolver.cpp
    resolvererror.cpp
    socket.cpp
    color.cpp

    PUBLIC
    # .h files
    constant_rate_loop.h
    liberror.h
    queue.h
    resolver.h
    resolvererror.h
    socket.h
    thread.h
    defs.h
    position.h
    direction.h
    snapshots.h
    gun_type.h
    client_actions.h
    server_message.h
    duck.h
    texturesize.h
    map.h
    projectiletype.h
    projectiledirection.h
    tiles.h
    size.h
    color.h
    clientidaction.h
    userlobbyinfo.h
    config.h
)
