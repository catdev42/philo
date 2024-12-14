/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 03:06:58 by myakoven          #+#    #+#             */
/*   Updated: 2024/12/14 18:54:21 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

/* THE PROGRAM OF EACH PHILOSOPHER*/
void	*dinner_each_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(),
		philo->table);
	pthread_mutex_lock(&philo->table->table_mutex);
	philo->table->active_threads += 1;
	pthread_mutex_unlock(&philo->table->table_mutex);
	if (philo->id % 2 == 0)
	{
		write_status(philo, THINKING);
		precise_usleep(philo->table->time_to_eat / 2, philo->table);
	}
	while (!sim_finished(philo->table))
	{
		if (philo->full)
			return (NULL);
		eat(philo);
		if (!sim_finished(philo->table))
			philo_sleep(philo);
		if (!sim_finished(philo->table))
			philo_think(philo);
	}
	return (NULL);
}

static int	pick_up_forks(t_philo *philo)
{
	safe_mutex_call(&philo->first_fork->fork, LOCK, philo->table);
	write_status(philo, TAKE_FIRST_FORK);
	if (sim_finished(philo->table))
	{
		safe_mutex_call(&philo->first_fork->fork, UNLOCK, philo->table);
		return (0);
	}
	safe_mutex_call(&philo->second_fork->fork, LOCK, philo->table);
	write_status(philo, TAKE_SECOND_FORK);
	return (1);
}

void	eat(t_philo *philo)
{
	if (philo->table->philo_num == 1)
	{
		write_status(philo, TAKE_FIRST_FORK);
		while (!sim_finished(philo->table))
			usleep(500);
	}
	else
	{
		if (!pick_up_forks(philo))
			return ;
		set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(),
			philo->table);
		write_status(philo, EATING);
		philo->meals_counter++;
		precise_usleep(philo->table->time_to_eat, philo->table);
		safe_mutex_call(&philo->first_fork->fork, UNLOCK, philo->table);
		safe_mutex_call(&philo->second_fork->fork, UNLOCK, philo->table);
	}
	if (philo->meals_counter == philo->table->meals_limit_num)
		set_bool(&philo->philo_mutex, &philo->full, true, philo->table);
}

void	philo_sleep(t_philo *philo)
{
	write_status(philo, SLEEPING);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}

void	philo_think(t_philo *philo)
{
	write_status(philo, THINKING);
	precise_usleep(philo->table->time_to_think, philo->table);
}

/*
	pthread_mutex_lock(&philo->table->table_mutex);
	philo->table->active_threads -= 1;
	pthread_mutex_unlock(&philo->table->table_mutex);

valgrind --tool=helgrind --trace-children=yes ./philo 4 410 200 200
--log-file=helgrind.log
*/
