#include "./include/philo.h"

// Just checks
void	*monitor_dinner(void *data)
{
	t_table *tab;
	// uint64_t current_time;
	int i;

	i = 0;
	tab = (t_table *)data;
	// wait for all threads to be active
	while (get_long(&tab->table_mutex, &tab->active_threads,
			tab) < tab->philo_nbr)
		;
	while (!sim_finished(tab))
	{
		i = 0;
		while (i < tab->philo_nbr && !sim_finished(tab))
		{
			// current_time = get_time();
			// if (!sim_finished(tab) && !tab->philos[i].full && current_time
			// 	- (uint64_t)tab->philos[i].last_meal_time > (uint64_t)tab->time_to_die)
			// {
			// 	write_status(&tab->philos[i], DIED);
			// 	set_bool(&tab->table_mutex, &tab->end_simulation, true, tab);
            //     break;
			// }
			i++;
		}
	}
	return (NULL);
}