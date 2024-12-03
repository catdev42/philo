#include "./include/philo.h"

// static bool	philo_died(t_philo *philo)
// {
// 	long	elapsed;
// 	long	t_to_die;

// 	if (get_bool(&philo->philo_mutex, &philo->full, philo->table))
// 		return (false);
// 	elapsed = get_time() - get_long(&philo->philo_mutex, &philo->last_meal_time,
// 			philo->table);
// 	t_to_die = philo->table->time_to_die;
// 	if (elapsed > t_to_die)
// 		return (true);
// 	return (false);
// }

// Just checks
void	*monitor_dinner(void *data)
{
	t_table *tab;
	uint64_t current_time;
	int i;
	// int full_count;
	long active_threads;

	i = 0;
	tab = (t_table *)data;
	// wait for all threads to be active
	active_threads = 0;
	while (active_threads < tab->philo_nbr)
		active_threads = get_long(&tab->table_mutex, &tab->active_threads, tab);
	while (!sim_finished(tab))
	{
		// i = 0;
		// full_count = 0;
		// while (i < tab->philo_nbr)
		// {
		// 	if (tab->philos[i].full)
		// 		full_count++;
		// 	if (full_count == tab->philo_nbr)
		// 		return (NULL);
		// 	i++;
		// }
		/**/
		i = 0;
		while (i < tab->philo_nbr && !sim_finished(tab))
		{
			current_time = get_time();
			// if (tab->philos[i].full && i == tab->philo_nbr - 1)
			// 	return (NULL);
			if (!tab->philos[i].full && current_time
				- (uint64_t)tab->philos[i].last_meal_time > (uint64_t)tab->time_to_die
				+ 10)
			{
				write_status(&tab->philos[i], DIED);
				set_bool(&tab->table_mutex, &tab->end_simulation, true, tab);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}