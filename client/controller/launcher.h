
#ifndef LAUNCHER_H
#define LAUNCHER_H



class Launcher {
    int argc;
    const char **argv;
public:
     void run_game();
     explicit Launcher(int argc, const char *argv[]);
};



#endif //LAUNCHER_H
