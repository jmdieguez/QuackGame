#include "constant_rate_loop.h"

using namespace std::chrono;

#define NANOSECONDS_PER_SECOND 1e9

template<typename T>
steady_clock::duration steady_duration(T seconds) {
    return steady_clock::duration(static_cast<int64_t>(seconds * NANOSECONDS_PER_SECOND));
}

ConstantRateLoop::ConstantRateLoop(bool &k_r, const double &r, const std::function<void(int)> &f) :
    keep_running(k_r), rate(r), func(f) {}

ConstantRateLoop::~ConstantRateLoop() {}

void ConstantRateLoop::execute() {
    steady_clock::time_point t1 = steady_clock::now();  // Initial time point
    int it = 0;

    while (keep_running) {
        func(it);

        steady_clock::time_point t2 = steady_clock::now();  // Current time point
        duration<double> elapsed = duration_cast<duration<double>>(t2 - t1);
        double rest = rate - elapsed.count();

        if (rest < 0) {
            // Calculate how many frames are missed and reset t1 to the correct point
            double behind = -rest;  // This is always positive
            double lost = behind - std::fmod(behind, rate);
            t1 += steady_duration(lost);
            it += static_cast<int>(lost / rate);  // Skip frames as needed
        } else {
            std::this_thread::sleep_for(duration<double>(rest));  // Wait to maintain rate
        }

        t1 += steady_duration(rate);
        ++it;  // Increment iteration
    }
}