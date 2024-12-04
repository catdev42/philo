/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 03:06:54 by myakoven          #+#    #+#             */
/*   Updated: 2024/12/04 03:06:55 by myakoven         ###   ########.fr       */
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

void	*monitor_thread(void *data)
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
				- (uint64_t)tab->philos[i].last_meal_time > (uint64_t)tab->time_to_die
				+ 5)
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
