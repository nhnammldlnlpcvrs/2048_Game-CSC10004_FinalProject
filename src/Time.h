#pragma once
#include <ctime>
#include <string>

struct Time {
    std::time_t startTime;
    std::time_t endTime;

    Time();

    void start();
    void stop();
    int getElapsedSeconds() const;
    std::string getFormattedTime() const;
};
