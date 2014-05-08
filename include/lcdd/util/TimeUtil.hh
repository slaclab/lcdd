#ifndef lcdd_util_TimeUtil_hh_
#define lcdd_util_TimeUtil_hh_ 1

#include <sys/time.h>

#include <string>
#include <map>
#include <iostream>

class TimeUtil {

    static std::map<std::string, long> _timerMap;

public:

    static long getNanoTime() {
        timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        return ts.tv_nsec;
    }

    static bool haveTimer(const std::string& name) {
        return _timerMap.count(name) != 0;
    }

    static void startTimer(const std::string& name) {
        _timerMap[name] = getNanoTime();
    }

    static long stopTimer(const std::string& name) {
        _timerMap[name] = getNanoTime() - _timerMap[name];
        return _timerMap[name];
    }

    static void addTime(const std::string& name, long nanos) {
        if (!haveTimer(name))
            createTimer(name);
        _timerMap[name] += nanos;
    }

    static void createTimer(const std::string& name) {
        _timerMap[name] = 0;
    }

    static long getTime(const std::string& name) {
        return _timerMap[name];
    }

    static void printOut(const std::string& name, std::ostream& os) {
        os << name << ": " << _timerMap[name] << std::endl;
    }

    static void clearTimers() {
        _timerMap.clear();
    }
};

#endif
