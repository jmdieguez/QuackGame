target_sources(quack_game_common
    PRIVATE
    # .cpp files
    constant_rate_loop.cpp
    liberror.cpp
    resolver.cpp
    resolvererror.cpp
    socket.cpp
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
    client_command_type.h
    client_command.h
    game_dto.h
    map_dto.h
    server_message.h
    )
