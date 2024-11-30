#include "./include/philo.h"

/*handle_thread_error will print the error and exit if there is an error*/
void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->nbr_limit_meals == 1)
		; // TODO
	else
		while (++i < table->philo_nbr)
			handle_thread_error(pthread_create(&table->philos[i].thread_id,
					NULL, dinner_simulation, (void *)&table->philos[i]), CREATE,
				table);
	handle_thread_error(pthread_create(&table->monitor, NULL, monitor_dinner,
			(void *)table), CREATE, table);
	table->start_simulation = get_time();
	if (!table->start_simulation)
		error_exit("Problem with gettimeofday()", 1, table);
	set_bool(&table->table_mutex, &table->all_threads_ready, true, table);
	i = -1;
	while (++i < table->philo_nbr)
		handle_thread_error(pthread_join(table->philos[i].thread_id, NULL),
			JOIN, table);
	handle_thread_error(pthread_join(table->monitor, NULL), JOIN, table);
	set_bool(&table->table_mutex, &table->end_simulation, true, table);
}

/* THE PROGRAM OF EACH PHILOSOPHER*/
void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	philo->last_meal_time = get_time();
	pthread_mutex_lock(&philo->table->table_mutex);
	philo->table->active_threads += 1;
	pthread_mutex_unlock(&philo->table->table_mutex);
	if (philo->id % 2 == 0)
		precise_usleep(philo->table->time_to_eat / 2, philo->table);
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
	// get forks
	safe_mutex_call(&philo->first_fork->fork, LOCK, philo->table);
	write_status(philo, TAKE_FIRST_FORK);
	safe_mutex_call(&philo->second_fork->fork, LOCK, philo->table);
	write_status(philo, TAKE_SECOND_FORK);
	// set last meal time (race conditions with checker so must lock)
	set_long(&philo->philo_mutex, &philo->last_meal_time, get_time(),
		philo->table);
	write_status(philo, EATING);
	philo->meals_counter++;
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->meals_counter == philo->table->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true, philo->table);
	// unlock and release forks
	safe_mutex_call(&philo->first_fork->fork, UNLOCK, philo->table);
	safe_mutex_call(&philo->second_fork->fork, UNLOCK, philo->table);
}

void	philo_sleep(t_philo *philo)
{
	write_status(philo, SLEEPING);
	precise_usleep(philo->table->time_to_sleep, philo->table);
}
void	philo_think(t_philo *philo)
{
	write_status(philo, THINKING);
}

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready, table))
		;
}

void	write_status(t_philo *philo, t_action action) //, bool debug
{
	long elapsed;

	if (philo->full)
		return ;
	elapsed = get_time() - philo->table->start_simulation;

	safe_mutex_call(&philo->table->write_mutex, LOCK, philo->table);

	if (!sim_finished(philo->table))
	{
		if (action == TAKE_FIRST_FORK || action == TAKE_SECOND_FORK)
			printf("%ld Philo %i has taken a fork\n", elapsed, philo->id);
		else if (action == EATING)
			printf(BOLD_BLUE "%ld Philo %i is eating...\n" RESET, elapsed,
				philo->id);
		else if (action == SLEEPING)
			printf("%ld Philo %i is sleeping...\n", elapsed, philo->id);
		else if (action == THINKING)
			printf("%ld Philo %i is thinking...\n", elapsed, philo->id);
		else if (action == DIED)
			printf(BOLD_RED "%ld Philo %i is DEAD...\n", elapsed, philo->id);
	}
	safe_mutex_call(&philo->table->write_mutex, UNLOCK, philo->table);
}

// void	actually_write(char *s1, char *s2, char *s3, char *s4)
// {
// 	if (s1)
// 		ft_putstr_fd(s1, 1);
// 	if (s2)
// 		ft_putstr_fd(s2, 1);
// 	if (s3)
// 		ft_putstr_fd(s3, 1);
// 	if (s4)
// 		ft_putstr_fd(s4, 1);
// }
