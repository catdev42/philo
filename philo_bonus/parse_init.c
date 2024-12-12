/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 03:06:23 by myakoven          #+#    #+#             */
/*   Updated: 2024/12/12 20:24:32 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

int	parse_argv(t_table *table, char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
		if (!ft_strisnumeric(argv[i]))
			error_exit("The arguments must be numeric", 1, table);
	table->philo_num = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->meals_limit_num = ft_atol(argv[5]);
	else
		table->meals_limit_num = -1;
	if (table->philo_num > INT_MAX || table->time_to_die > INT_MAX
		|| table->time_to_eat > INT_MAX || table->time_to_sleep > INT_MAX
		|| table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		error_exit("The number is too big, INT_MAX is limit", 1, table);
	return (1);
}

int	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = false;
	table->active_threads = 0;
	table->philos = (t_philo *)safe_calloc(table->philo_num + 1,
			sizeof(t_philo), table);
	table->forks = (t_fork *)safe_calloc(table->philo_num + 1, sizeof(t_fork),
			table);
	safe_mutex_call(&table->table_mutex, INIT, table);
	safe_mutex_call(&table->write_mutex, INIT, table);
	while (i < table->philo_num)
	{
		safe_mutex_call(&table->forks[i].fork, INIT, table);
		table->forks->fork_id = i;
		i++;
	}
	return (i);
}

void	philo_init(t_table *table)
{
	int	i;
	int	philo_num;

	philo_num = table->philo_num;
	i = 0;
	while (i < philo_num)
	{
		table->philos[i].id = i + 1;
		table->philos[i].full = false;
		table->philos[i].meals_counter = 0;
		table->philos[i].table = table;
		table->philos[i].first_fork = &table->forks[i];
		table->philos[i].second_fork = &table->forks[(i + 1) % philo_num];
		if (table->philos[i].id % 2 == 0)
		{
			table->philos[i].first_fork = &table->forks[(i + 1) % philo_num];
			table->philos[i].second_fork = &table->forks[i];
		}
		safe_mutex_call(&table->philos[i].philo_mutex, INIT, table);
		i++;
	}
}

int	ft_strisnumeric(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (i < ft_strlen(str))
		return (0);
	return (1);
}