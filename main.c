/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 03:06:54 by myakoven          #+#    #+#             */
/*   Updated: 2024/12/14 18:54:32 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	ft_memset(&table, 0, sizeof(t_table));
	if ((argc != 5 && argc != 6) || !argv[0])
		error_exit("Wrong input!\n" GREEN "DO: /philo 4 400 200 200 4", 1,
			&table);
	parse_argv(&table, argv);
	data_init(&table);
	philo_init(&table);
	dinner_start(&table);
	clean(&table);
	return (0);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->meals_limit_num == 0)
		return ;
	else
		while (++i < table->philo_num)
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
	while (++i < table->philo_num)
		handle_thread_error(pthread_join(table->philos[i].thread_id, NULL),
			JOIN, table);
	set_bool(&table->table_mutex, &table->end_simulation, true, table);
	handle_thread_error(pthread_join(table->monitor, NULL), JOIN, table);
}

static int	is_still_alive(t_table *table, int i)
{
	long		last_meal_time;
	bool		is_full;
	uint64_t	current_time;

	current_time = get_time();
	last_meal_time = get_long(&table->philos[i].philo_mutex,
			&table->philos[i].last_meal_time, table);
	is_full = get_bool(&table->philos[i].philo_mutex, &table->philos[i].full,
			table);
	if (!is_full && (current_time
			- (uint64_t)last_meal_time) > (uint64_t)table->time_to_die + 5)
		return (0);
	return (1);
}

void	*monitor_thread(void *data)
{
	t_table	*tab;
	int		i;

	i = 0;
	tab = (t_table *)data;
	while (i < tab->philo_num)
	{
		i = get_long(&tab->table_mutex, &tab->active_threads, tab);
		usleep(100);
	}
	while (!sim_finished(tab))
	{
		i = -1;
		while (++i < tab->philo_num && !sim_finished(tab))
		{
			if (!is_still_alive(tab, i))
			{
				write_status(&tab->philos[i], DIED);
				set_bool(&tab->table_mutex, &tab->end_simulation, true, tab);
				return (NULL);
			}
		}
	}
	return (NULL);
}

/*current_time
	- (uint64_t)tab->philos[i].last_meal_time > (uint64_t)tab->time_to_die + 5*/
