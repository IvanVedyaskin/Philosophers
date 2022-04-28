#include "philo.h"

struct timeval ft_usleep(long int time)
{
    long int		i;
    struct timeval  start_time;
    struct timeval  tmp;
    long int        time_limit;

    gettimeofday(&start_time, 0);
//	printf ("lol = %d\n",time);
	usleep(time - 5000);
    time_limit = start_time.tv_sec * 1000 + start_time.tv_usec / 1000;
    while (1)
    {
        gettimeofday(&tmp, 0);
        i = (tmp.tv_sec * 1000 + tmp.tv_usec / 1000) - time_limit;
        if (i >= time / 1000)
            return (start_time);
        usleep(500);
    }
}