#ifndef lcdd_util_TimerUtil_hh_
#define lcdd_util_TimerUtil_hh_ 1

#include <sys/time.h>

// clock_gettime is not defined on MacOS
#ifdef __MACH__
#include <mach/mach_time.h>
#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 0
int clock_gettime(int clk_id, struct timespec *t){
    mach_timebase_info_data_t timebase;
    mach_timebase_info(&timebase);
    uint64_t time;
    time = mach_absolute_time();
    double nseconds = ((double)time * (double)timebase.numer)/((double)timebase.denom);
    double seconds = ((double)time * (double)timebase.numer)/((double)timebase.denom * 1e9);
    t->tv_sec = seconds;
    t->tv_nsec = nseconds;
    return 0;
}
#endif



#include <string>
#include <map>
#include <iostream>

class TimerUtil {

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
