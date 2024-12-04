#include "./include/philo.h"

typedef struct s_mute_chopstick
{
	int				num;
	pthread_mutex_t	mutex;
}					t_mute_chopstick;\



void	free_mutex_chop(t_mute_chopstick *data)
{
	pthread_mutex_destroy(&data->mutex);
	free(data);
}

t_mute_chopstick	*make_chopstick(void)
{
	t_mute_chopstick	*chopstick;

	chopstick = NULL;
	chopstick = malloc(sizeof(t_mute_chopstick));
	if (chopstick == NULL)
		exit(1);
	chopstick->num = 0;
	pthread_mutex_init(&chopstick->mutex, NULL);
	return (chopstick);
}

void	*iter_num(void *mut_num)
{
	t_mute_chopstick	*data;
	int					i;

	i = 0;
	data = (t_mute_chopstick *)mut_num;
	while (i < 1000)
	{
		pthread_mutex_lock(&data->mutex);
		(data->num)++;
		pthread_mutex_unlock(&data->mutex);
		i++;
	}
	return (NULL);
}

void	mutex_example(void)
{
	t_mute_chopstick	*chopstick;
	pthread_t			philo_1;
	pthread_t			philo_2;

	chopstick = make_chopstick();
	if (pthread_create(&philo_1, NULL, iter_num, (void *)chopstick))
		exit(1); // TODO CLEANING
	if (pthread_create(&philo_2, NULL, iter_num, (void *)chopstick))
		exit(1); // TODO CLEANING
	if (pthread_join(philo_1, NULL))
		exit(1);
	if (pthread_join(philo_2, NULL))
		exit(1);
	printf("Num: %d\n", chopstick->num);
	free_mutex_chop(chopstick);
}

int	main(void)
{
	// firstphilo();
	mutex_example();
}

void	firstphilo(void)
{
	pthread_t philo_1;
	pthread_t philo_2;
	int p_1;
	int p_2;

	p_1 = 1;
	p_2 = 2;
	if (pthread_create(&philo_1, NULL, phil_eating, (void *)&p_1))
		exit(1); // TODO CLEANING
	if (pthread_join(philo_1, NULL))
		exit(1);
	if (pthread_create(&philo_2, NULL, phil_eating, (void *)&p_2))
		exit(1); // TODO CLEANING
	if (pthread_join(philo_2, NULL))
		exit(1);
}