#include "philo_one.h"

// struct timeval tv1,tv2,dtv;

// struct timezone tz;

// void time_start(void)
// {
// 	gettimeofday(&tv1, &tz);
// }

ssize_t get_time(ssize_t begin_time)
{
	timing t1;

	gettimeofday(&t1, NULL);
	return ((t1.tv_sec * 1000 + t1.tv_usec / 1000) - begin_time);
}

// long time_stop(void)
// {
// 	gettimeofday(&tv2, &tz);
// 	dtv.tv_sec= tv2.tv_sec -tv1.tv_sec;
// 	dtv.tv_usec=tv2.tv_usec-tv1.tv_usec;
// 	if(dtv.tv_usec < 0)
// 	{
// 		dtv.tv_sec--;
// 		dtv.tv_usec += 1000000;
// 	}
// 	return (dtv.tv_sec * 1000 + dtv.tv_usec / 1000);
// }
