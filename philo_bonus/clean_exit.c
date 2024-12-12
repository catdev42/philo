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
		printf(RED "%s" RESET, error);
	exit(error_num);
}

void	clean(t_table *table)
{
	int	i;

	safe_mutex_call(&table->table_mutex, DESTROY, table);
	safe_mutex_call(&table->write_mutex, DESTROY, table);
	i = 0;
	while (i < table->philo_num)
	{
		safe_mutex_call(&table->forks[i].fork, DESTROY, table);
		safe_mutex_call(&table->philos[i++].philo_mutex, DESTROY, table);
	}
	free(table->philos);
	free(table->forks);
}
