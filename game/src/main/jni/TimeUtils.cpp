//
// Created by qwerty on 19.09.16.
//

#include "TimeUtils.h"

double TimeUtils::now() {
    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;
}