#include "philo.h"

void ft_usleep(long int time)
{
    int             i;
    struct timeval  start_time;
    struct timeval  tmp;
    long int        time_limit;

    // printf ("time = %ld\n", time);
    gettimeofday(&start_time, 0);
    time_limit = start_time.tv_sec * 1000000 + start_time.tv_usec + time;
    // printf ("before = %ld\n", start_time.tv_sec * 1000000 + start_time.tv_usec + time);
    i = 0;
    while (i >= 0)
    {
        gettimeofday(&tmp, 0);
        // printf ("after = %ld\n", tmp.tv_sec * 1000000 + tmp.tv_usec);
        i = (time_limit) - (tmp.tv_sec * 1000000 + tmp.tv_usec);
        //  printf ("time_check = %d\n", i);
        if (i < 0)
            break; 
        usleep(i);
    }
}