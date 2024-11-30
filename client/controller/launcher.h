//
// Created by trini-taller on 11/30/24.
//

#ifndef LAUNCHER_H
#define LAUNCHER_H



class Launcher {
    const char *host;
    const char *port;
public:
     void run_game();
     explicit Launcher(const char *host, const char *port)
};



#endif //LAUNCHER_H
