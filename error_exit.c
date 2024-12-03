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
	while (i < table->philo_nbr)
	{
		safe_mutex_call(&table->forks[i].fork, DESTROY, table);
		safe_mutex_call(&table->philos[i++].philo_mutex, DESTROY, table);
	}
	free(table->philos);
	free(table->forks);
}
