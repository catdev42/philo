#include "./include/philo.h"

void	*monitor_dinner(void *data)
{
	t_table *tab;
	uint64_t current_time;
	int i;
	long active_threads;

	i = 0;
	tab = (t_table *)data;
	active_threads = 0;
	while (active_threads < tab->philo_nbr)
		active_threads = get_long(&tab->table_mutex, &tab->active_threads, tab);
	while (!sim_finished(tab))
	{
		i = 0;
		while (i < tab->philo_nbr && !sim_finished(tab))
		{
			current_time = get_time();
			if (!tab->philos[i].full && current_time
				- (uint64_t)tab->philos[i].last_meal_time > (uint64_t)tab->time_to_die)
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