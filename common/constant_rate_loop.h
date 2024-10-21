#ifndef CONSTANT_RATE_LOOP_H
#define CONSTANT_RATE_LOOP_H

#include <functional>
#include <atomic>

class ConstantRateLoop {
private:
    std::atomic<bool> &keep_running;
    const double rate;
    const std::function<void(int)> func;

public:
    // Keep running, rate, function
    ConstantRateLoop(std::atomic<bool> &k_r, const double &r, const std::function<void(int)> &f);
    ~ConstantRateLoop();

    void execute();
};

#endif // CONSTANT_RATE_LOOP_H