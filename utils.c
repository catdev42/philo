#include "./include/philo.h"

/* Returns current time tine EPOHC in milliseconds */
uint64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/* PRECISE USLEEP */
void	precise_usleep(long milsec_long, t_table *table)
{
	// long usec;
	uint64_t milsec = (uint64_t)milsec_long;
	uint64_t start;
	start = get_time();
	while (get_time() - start < milsec)
	{
		if (sim_finished(table))
			break ;
		if (milsec - (get_time() - start) > milsec / 10)
			usleep(milsec / 10);
		else
			while (get_time() - start < milsec)
				;
	}
	return ;
}