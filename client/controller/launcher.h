
#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <string>


class Launcher {
private:
    int argc;
    const char **argv;
    void show_result();
    std::string winner = "";
public:
     void run_game();
     explicit Launcher(int argc, const char *argv[]);
};



#endif //LAUNCHER_H
