/*
 * interactive.c
 *
 * Sleeps for CLICK_INTERVAL_MS between "clicks" and reports:
 *   - elapsed time since click (ms, 3 decimals)
 *   - instantaneous jitter for THIS click (ms, 3 decimals)
 *
 * jitter_ms = actual_interval_ms - CLICK_INTERVAL_MS
 *
 * Usage:
 *   ./interactive <runtime_seconds>
 */

#define _POSIX_C_SOURCE 199309L//I was having issues with CLOCK_MONOTONIC, saying 'identifier "CLOCK_MONOTONIC" is undefined'
#define _DEFAULT_SOURCE //I was having issues with usleep that adding this resolved


#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define CLICK_INTERVAL_MS 300.0


int main(int argc, char *argv[]) {
    // TODO
    int runSeconds = atoi(argv[1]);
    
    struct timespec ts;
    //int startTime = clock_gettime(CLOCK_MONOTONIC, &ts);
    
    /*
    clock_gettime(CLOCK_MONOTONIC, &ts);
    double startSeconds = ts.tv_sec + ts.tv_nsec / 1e9;
    double startMilli = ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
    */
    
    //double ogPreviousTime = clock_gettime(CLOCK_MONOTONIC, &ts); 
    clock_gettime(CLOCK_MONOTONIC, &ts); 
    double ogPrevSec = ts.tv_sec + ts.tv_nsec / 1e9; 
    double ogPrevMilli = ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6; 
    //double preTime = 0;
    //double preSec = 0;
    //double preMil = 0;

    //double currentTime = 0; //small
    double totalTime = 0; //small
    while(totalTime<runSeconds){
        //important code
        //printf("pS: %f pM: %f\n", preSec, preMil);
        usleep(CLICK_INTERVAL_MS*1000);


        //double ogCurrentTime = clock_gettime(CLOCK_MONOTONIC, &ts); 
        clock_gettime(CLOCK_MONOTONIC, &ts); 
        //double currentTime = ogCurrentTime - ogPreviousTime; 

        //currentTime = currentTime - startTime;
        double ogCurrentSeconds = ts.tv_sec + ts.tv_nsec / 1e9;
        double ogCurrentMilli = ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
        double currentSeconds = ogCurrentSeconds - ogPrevSec;
        double currentMilli = ogCurrentMilli - ogPrevMilli;


        //printf("cS: %f cM: %f\n", currentSeconds, currentMilli);

        double currentTime = currentSeconds + currentMilli/1000;
        //printf("Time Check: %f\n", currentTime);//testing
        double currentMilliTime = currentTime * 1000; //convert to milliseconds

        double jitter = currentMilli - CLICK_INTERVAL_MS;
        printf("[click] elapsed: %f ms jitter: %f\n", currentMilli, jitter);

        //ogPreviousTime = ogCurrentTime;
        ogPrevSec = ogCurrentSeconds;
        ogPrevMilli = ogCurrentMilli;
        totalTime = totalTime + currentTime;
        //printf("cS: %f cM: %f\n", currentSeconds, currentMilli);
        //printf("pS: %f pM: %f\n", preSec, preMil);
    }
    return 0;
}
