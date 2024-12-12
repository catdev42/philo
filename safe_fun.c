/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 03:06:29 by myakoven          #+#    #+#             */
/*   Updated: 2024/12/12 20:17:09 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/philo.h"

void	*safe_calloc(size_t nmemb, size_t size, t_table *table)
{
	void	*ptr;

	ptr = NULL;
	ptr = ft_calloc(nmemb, size);
	if (ptr == NULL)
		error_exit("Allocation Error", 1, table);
	return (ptr);
}

void	handle_mutex_error(int status, int oper, t_table *table)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (oper == LOCK || oper == UNLOCK))
		error_exit(" The value specified by mutex is invalid.", 1, table);
	else if (status == EINVAL && oper == INIT)
		error_exit("The value specified by attr is invalid.", 1, table);
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if thread blocked waiting for mutex",
			1, table);
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mut", 1, table);
	else if (status == ENOMEM)
		error_exit("Mutex memory error.", 1, table);
	else if (status == EBUSY)
		error_exit("Mutex si locked.", 1, table);
}

void	safe_mutex_call(t_mtx *mutex, int operation, t_table *table)
{
	if (operation == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), operation, table);
	else if (operation == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), operation, table);
	else if (operation == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), operation, table);
	else if (operation == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), operation, table);
	else
		error_exit("Wrong operation code", 1, table);
}

void	handle_thread_error(int status, int oper, t_table *table)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("No resource to crete another thread", 1, table);
	else if (status == EPERM)
		error_exit("The caller does not have appropriate permissions", 1,
			table);
	else if (status == EINVAL && oper == CREATE)
		error_exit("The value specified by attr is invalid", 1, table);
	else if (status == EINVAL && (oper == JOIN || oper == DETACH))
		error_exit("The value specified by thread is not joinable", 1, table);
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding to thread ID.", 1,
			table);
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value of"
			"thread specifies the calling thread", 1, table);
}
