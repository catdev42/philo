/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 03:06:45 by myakoven          #+#    #+#             */
/*   Updated: 2024/12/14 13:49:03 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				usleep(500);
	}
	return ;
}


void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready, table))
		usleep(100);
}

void	write_status(t_philo *philo, t_action action)
{
	long	elapsed;

	if (philo->full)
		return ;
	elapsed = get_time() - philo->table->start_simulation;
	safe_mutex_call(&philo->table->write_mutex, LOCK, philo->table);
	if (!sim_finished(philo->table))
	{
		if (action == TAKE_FIRST_FORK || action == TAKE_SECOND_FORK)
			printf("%ld Philo %i has taken a fork\n", elapsed, philo->id);
		else if (action == EATING)
			printf(BOLD_BLUE "%ld Philo %i is eating\n" RESET, elapsed,
				philo->id);
		else if (action == SLEEPING)
			printf("%ld Philo %i is sleeping\n", elapsed, philo->id);
		else if (action == THINKING)
			printf("%ld Philo %i is thinking\n", elapsed, philo->id);
		else if (action == DIED)
			printf(BOLD_RED "%ld Philo %i died\n", elapsed, philo->id);


	}
	safe_mutex_call(&philo->table->write_mutex, UNLOCK, philo->table);
}

/* Delivers a long int
	- user must make sure the nubmer is not more or it will overflow */
long	ft_atol(const char *nptr)
{
	long	num;
	long	sign;

	num = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '+')
			nptr++;
		else if (*nptr == '-')
		{
			sign = -1;
			nptr++;
		}
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = num * 10 + (*nptr - 48);
		nptr++;
	}
	return (num * sign);
}


