#include "Time.h"
#include <sstream>
#include <iomanip>

Time::Time() {
    startTime = 0;
    endTime = 0;
}

void Time::start() {
    startTime = std::time(nullptr);
}

void Time::stop() {
    endTime = std::time(nullptr);
}

int Time::getElapsedSeconds() const {
    return static_cast<int>(endTime - startTime);
}

std::string Time::getFormattedTime() const {
    int duration = getElapsedSeconds();
    int minutes = duration / 60;
    int seconds = duration % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}
