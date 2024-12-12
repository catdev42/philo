/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 03:07:06 by myakoven          #+#    #+#             */
/*   Updated: 2024/12/12 20:24:16 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	error_exit(const char *error, int error_num, t_table *table)
{
	clean(table);
	if (error)
		printf(BOLD_RED "%s" RESET, error);
	exit(error_num);
}

void	clean(t_table *table)
{
	int	i;

	if (table->mut_inited)
		safe_mutex_call(&table->table_mutex, DESTROY, table);
	if (table->mut_inited)
		safe_mutex_call(&table->write_mutex, DESTROY, table);
	i = 0;
	while (i < table->philo_num && i < table->fork_mut_inited)
	{
		if (table->forks)
			safe_mutex_call(&table->forks[i].fork, DESTROY, table);
		if (table->philos)
			safe_mutex_call(&table->philos[i].philo_mutex, DESTROY, table);
		i++;
	}
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
}
