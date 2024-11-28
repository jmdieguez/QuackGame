#ifndef SERVER_GUN_SPAWN_H
#define SERVER_GUN_SPAWN_H

#include <random>

#define INITIAL_TIME_TO_SPAWN 90   // 3 Seconds
#define MINIMUM_TIME_TO_SPAWN 270  // 9 Seconds
#define MAXIMUM_TIME_TO_SPAWN 810  // 27 Seconds

class GunSpawn {
private:
    unsigned iterations_until_spawn;
public:
    GunSpawn() : iterations_until_spawn(INITIAL_TIME_TO_SPAWN) {}
    ~GunSpawn() {}

    // Returns true if iterations_until_spawn gets to 0.
    // Then its value is updated to a random number between MINIMUM_TIME_TO_SPAWN and MAXIMUM_TIME_TO_SPAWN
    bool step() {
        // Don't decrease the timer if it's already 0.
        if (iterations_until_spawn == 0)
            return true;

        return (--iterations_until_spawn == 0);
    }

    void restart() {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<unsigned> dist(MINIMUM_TIME_TO_SPAWN, MAXIMUM_TIME_TO_SPAWN);
        iterations_until_spawn = dist(rng);
    }
};

#endif // SERVER_GUN_SPAWN_H
