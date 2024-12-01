#ifndef PLAYER_KEY_CONFIG_MANAGER_H
#define PLAYER_KEY_CONFIG_MANAGER_H

#include <unordered_map>
#include <vector>
#include "playerkeyconfig.h"
#include "command.h"

class PlayerKeyConfigManager
{
private:
    std::vector<PlayerKeyConfig> player_configs;

public:
    PlayerKeyConfigManager();
    const PlayerKeyConfig &get_player_config(size_t player_index) const;
    ~PlayerKeyConfigManager();
};

#endif // PLAYER_KEY_CONFIG_MANAGER_H