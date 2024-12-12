/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 03:06:35 by myakoven          #+#    #+#             */
/*   Updated: 2024/12/12 20:20:37 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

/* Slightly abstacts working with mutex,
these will call LOCK and UNLOCK and perform error handling */
void	set_bool(t_mtx *mutex, bool *item, bool value, t_table *table)
{
	safe_mutex_call(mutex, LOCK, table);
	*item = value;
	safe_mutex_call(mutex, UNLOCK, table);
}

bool	get_bool(t_mtx *mutex, bool *item, t_table *table)
{
	bool	ret;

	safe_mutex_call(mutex, LOCK, table);
	ret = *item;
	safe_mutex_call(mutex, UNLOCK, table);
	return (ret);
}

void	set_long(t_mtx *mutex, long *item, long value, t_table *table)
{
	safe_mutex_call(mutex, LOCK, table);
	*item = value;
	safe_mutex_call(mutex, UNLOCK, table);
}

long	get_long(t_mtx *mutex, long *item, t_table *table)
{
	long	ret;

	safe_mutex_call(mutex, LOCK, table);
	ret = *item;
	safe_mutex_call(mutex, UNLOCK, table);
	return (ret);
}

bool	sim_finished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation, table));
}
