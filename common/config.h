#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <yaml-cpp/yaml.h>

class Config
{
private:
    YAML::Node config;

public:
    static Config &getInstance()
    {
        static Config instance;
        return instance;
    }

    void load(const std::string &filename)
    {
        config = YAML::LoadFile(filename);
    }

    YAML::Node operator[](const std::string &key) const
    {
        return config[key];
    }

    ~Config() {};
};

#endif // CONFIG_H