/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 03:06:58 by myakoven          #+#    #+#             */
/*   Updated: 2024/12/04 03:06:59 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else
		while (++i < table->philo_nbr)
			handle_thread_error(pthread_create(&table->philos[i].thread_id,
					NULL, dinner_each_philo, (void *)&table->philos[i]), CREATE,
				table);
	handle_thread_error(pthread_create(&table->monitor, NULL, monitor_thread,
			(void *)table), CREATE, table);
	table->start_simulation = get_time();
	if (!table->start_simulation)
		error_exit("Problem with gettimeofday()", 1, table);
	set_bool(&table->table_mutex, &table->all_threads_ready, true, table);
	i = -1;
	while (++i < table->philo_nbr)
		handle_thread_error(pthread_join(table->philos[i].thread_id, NULL),
			JOIN, table);
	set_bool(&table->table_mutex, &table->end_simulation, true, table);
	handle_thread_error(pthread_join(table->monitor, NULL), JOIN, table);
}

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
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	if (philo->table->philo_nbr == 1)
	{
		write_status(philo, TAKE_FIRST_FORK);
		while (!sim_finished(philo->table))
			usleep(500);
	}
	else
	{
		safe_mutex_call(&philo->first_fork->fork, LOCK, philo->table);
		write_status(philo, TAKE_FIRST_FORK);
		safe_mutex_call(&philo->second_fork->fork, LOCK, philo->table);
		write_status(philo, TAKE_SECOND_FORK);
		set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(),
			philo->table);
		write_status(philo, EATING);
		philo->meals_counter++;
		precise_usleep(philo->table->time_to_eat, philo->table);
		safe_mutex_call(&philo->first_fork->fork, UNLOCK, philo->table);
		safe_mutex_call(&philo->second_fork->fork, UNLOCK, philo->table);
	}
	if (philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true, philo->table);
}

void	philo_sleep(t_philo *philo)
{
	write_status(philo, SLEEPING);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}
void	philo_think(t_philo *philo)
{
	long	think1;
	long	think2;

	think1 = 0;
	think2 = 0;
	if (philo->table->philo_nbr % 2)
	{
		think1 = philo->table->time_to_die - philo->table->time_to_sleep
			- philo->table->time_to_eat;
		think2 = philo->table->time_to_eat + 30;
		if (think2 < think1)
			think1 = think2;
	}
	write_status(philo, THINKING);
	precise_usleep(think1, philo->table);
}
