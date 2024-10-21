#include "constant_rate_loop.h"

#include <cmath>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;

ConstantRateLoop::ConstantRateLoop(std::atomic<bool> &k_r, const double &r, const std::function<void(unsigned int)> &f) :
    keep_running(k_r), rate(r), func(f) {}

ConstantRateLoop::~ConstantRateLoop() {}

void ConstantRateLoop::execute() {
    steady_clock::time_point t1 = steady_clock::now();  // Initial time point
    unsigned int it = 0;

    while (keep_running.load()) {
        func(it);

        steady_clock::time_point t2 = steady_clock::now();  // Current time point
        duration<double> elapsed = duration_cast<duration<double>>(t2 - t1);
        double rest = rate - elapsed.count();

        if (rest < 0) {
            // Calculate how many frames are missed and reset t1 to the correct point
            double behind = -rest;  // This is always positive
            double lost = behind - std::fmod(behind, rate);
            t1 += duration_cast<steady_clock::duration>(duration<double>(lost));
            it += static_cast<int>(lost / rate);  // Skip frames as needed
        } else {
            std::this_thread::sleep_for(duration<double>(rest));  // Wait to maintain rate
        }

        t1 += duration_cast<steady_clock::duration>(duration<double>(rate));
        ++it;  // Increment iteration
    }
}