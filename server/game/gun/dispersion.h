#ifndef DISPERSION_H
#define DISPERSION_H

#include <random>

class Dispersion
{
private:
public:
    Dispersion() {};
    void apply_dispersion(std::pair<int, int> &directions, int value_dispersion)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, value_dispersion);
        int random_number = dist(gen) == 0 ? -value_dispersion : value_dispersion;
        if (directions.first != 0)
            directions.second += random_number;
        else if (directions.second < 0)
            directions.first += random_number;
    }
    std::vector<std::pair<int, int>> apply_dispersion_shotgun(const std::pair<int, int> &direction)
    {
        std::vector<std::pair<int, int>> directions;

        if (direction.first == 1)

            directions = {{1, 0}, {1, 1}, {1, -1}, {1, 3}, {1, 2}, {1, -2}};

        if (direction.first == -1)

            directions = {{-1, 0}, {-1, 1}, {-1, -1}, {-1, 3}, {-1, 2}, {-1, -2}};

        if (direction.second == -1)

            directions = {{0, -1}, {1, -1}, {-1, -1}, {0, -3}, {1, -2}, {-1, -2}};

        return directions;
    }

    ~Dispersion() {};
};

#endif // DISPERSION_H