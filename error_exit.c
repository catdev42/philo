#include "./include/philo.h"

void	error_exit(const char *error, int error_num, t_table *table)
{
	clean(table);
	if (error)
	{
		ft_putstr_fd(BOLD_RED, 2);
		ft_putstr_fd(error, 2);
		ft_putstr_fd(RESET, 2);
	}
	// exit(1);
	exit(error_num);
}

void	clean(t_table *table)
{
	int	i;

	safe_mutex_call(&table->table_mutex, DESTROY, table);
	safe_mutex_call(&table->write_mutex, DESTROY, table);
	i = 0;
	while (i < table->philo_nbr)
	{
		safe_mutex_call(&table->forks[i].fork, DESTROY, table);
		safe_mutex_call(&table->philos[i++].philo_mutex, DESTROY, table);
	}
	free(table->philos);
	free(table->forks);
}
