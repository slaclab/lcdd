#ifndef lcdd_util_TimeUtil_hh_
#define lcdd_util_TimeUtil_hh_

#include <sys/time.h>

class TimeUtil {

public:

    static long getNanoTime() {
        timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        return ts.tv_nsec;
    }
};

#endif
