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
	if (table)
		ft_putstr_fd("TODO CLEAN", 2);
}