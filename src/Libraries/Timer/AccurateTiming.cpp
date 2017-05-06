#include "AccurateTiming.h"
#include<time.h>
#include <chrono>

//*****************************************************
//*****************************************************
//********** DELAY FOR # uS WITHOUT SLEEPING **********
//*****************************************************
//*****************************************************
//Using delayMicroseconds lets the linux scheduler decide to jump to another process.  Using this function avoids letting the
//scheduler know we are pausing and provides much faster operation if you are needing to use lots of delays.
void uDelay(unsigned int delay_us){
    long int start_time;
    long int time_difference;
    struct timespec gettime_now;

    clock_gettime(CLOCK_REALTIME, &gettime_now);
    start_time = gettime_now.tv_nsec;		//Get nS value
    while (1)
    {
        clock_gettime(CLOCK_REALTIME, &gettime_now);
        time_difference = gettime_now.tv_nsec - start_time;
        if (time_difference < 0)
            time_difference += 1000000000;				//(Rolls over every 1 second)
        if (time_difference > (delay_us * 1000))		//Delay for # nS
            break;
    }

}

//*****************************************************
//*****************************************************
//********** DELAY FOR # mS WITHOUT SLEEPING **********
//*****************************************************
//*****************************************************
//Using delayMicroseconds lets the linux scheduler decide to jump to another process.  Using this function avoids letting the
//scheduler know we are pausing and provides much faster operation if you are needing to use lots of delays.
void mDelay(unsigned int delay_ms){
    unsigned int microseconds;
//    long int start_time;
//    long int time_difference;
//    struct timespec gettime_now;

//    clock_gettime(CLOCK_REALTIME, &gettime_now);
//    start_time = gettime_now.tv_nsec;		//Get nS value
    auto startTime = std::chrono::high_resolution_clock::now();
    while (1)
    {
//        clock_gettime(CLOCK_REALTIME, &gettime_now);
//        time_difference = gettime_now.tv_nsec - start_time;
        auto elapsedTime = std::chrono::high_resolution_clock::now() - startTime;
        microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsedTime).count();        
//        if (time_difference < 0)
//            time_difference += 1000000000;				//(Rolls over every 1 second)
        if (microseconds > (delay_ms * 1000))		//Delay for # nS
            break;
    }

}