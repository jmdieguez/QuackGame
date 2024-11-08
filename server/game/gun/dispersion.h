#include <random>

class Dispersion
{
private:
public:
    Dispersion() {};
    void apply_dispersion(std::pair<int, int> &directions)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 1);
        int random_number = dist(gen) == 0 ? -1 : 1;
        if (directions.first != 0)
            directions.second += random_number;
        else if (directions.second < 0)
            directions.first += random_number;
    }

    ~Dispersion() {};
};
