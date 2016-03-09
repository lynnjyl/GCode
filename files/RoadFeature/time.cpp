//
//  time.cpp
//  
//
//  Created by XoX on 15/9/17.
//
//

#include <stdio.h>
#include <sys/time.h>

double wallclock(void)
{
    struct timeval tv;
    struct timezone tz;
    double t;
    
    gettimeofday(&tv, &tz);
    
    t = (double)tv.tv_sec*1000;
    t += ((double)tv.tv_usec)/1000.0;
    
    return t;
}
