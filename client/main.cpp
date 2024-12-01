#include <iostream>
#include "controller/launcher.h"
#include "../common/config.h"

#define OK 0
#define HOST 1
#define PORT 2
#define MIN_ARGS 3
#define ERROR -1
#define CONFIG_PATH "config/client.yaml"

int main(int argc, const char *argv[])
{
    if (argc != MIN_ARGS)
        return ERROR;

    try
    {
        Config::getInstance().load(CONFIG_PATH);
        Launcher launcher(argc, argv);
        launcher.run_game();
    }
    catch (const std::exception &err)
    {
        std::cerr << "Something went wrong and an exception was caught: " << err.what()
                  << std::endl;
        return ERROR;
    }
    catch (...)
    {
        std::cerr << "Something went wrong and an unknown exception was caught." << std::endl;
        return ERROR;
    }
    return OK;
}