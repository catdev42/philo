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
