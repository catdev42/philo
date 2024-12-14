/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 03:06:45 by myakoven          #+#    #+#             */
/*   Updated: 2024/12/14 13:52:19 by myakoven         ###   ########.fr       */
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
	uint64_t	milsec;
	uint64_t	start;

	milsec = (uint64_t)milsec_long;
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
		usleep(200);
}

void	write_status(t_philo *philo, t_action action)
{
	long	elapsed;
	bool	is_full;

	is_full = get_bool(&philo->philo_mutex, &philo->full, philo->table);
	if (is_full)
		return ;
	elapsed = get_time() - philo->table->start_simulation;
	safe_mutex_call(&philo->table->write_mutex, LOCK, philo->table);
	if (!sim_finished(philo->table))
	{
		if (action == TAKE_FIRST_FORK || action == TAKE_SECOND_FORK)
			printf("%ld %i has taken a fork\n", elapsed, philo->id);
		else if (action == EATING)
			printf(BOLD_BLUE "%ld %i is eating\n" RESET, elapsed,
				philo->id);
		else if (action == SLEEPING)
			printf("%ld %i is sleeping\n", elapsed, philo->id);
		else if (action == THINKING)
			printf("%ld %i is thinking\n", elapsed, philo->id);
		else if (action == DIED)
			printf(BOLD_RED "%ld %i died\n", elapsed, philo->id);
		else if (action == DEBUG)
			printf(BOLD_RED "%ld %i SOMETHING IS WEIRD\n" RESET, elapsed, philo->id);
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
