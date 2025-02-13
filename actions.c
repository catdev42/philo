#include "./include/philo.h"

void	*phil_eating(void *phil_num)
{
	int	*p;

	p = (int *)phil_num;
	ft_putstr_fd("philo ", 1);
	ft_putnbr_fd(*p, 1);
	ft_putstr_fd(" is eating...\n", 1);
	return (NULL);
}
void	*phil_thinking(void *phil_num)
{
    int	*p;

	p = (int *)phil_num;
	ft_putstr_fd("philo ", 1);
	ft_putnbr_fd(*p, 1);
	ft_putstr_fd(" is thinking...\n", 1);
    	return (NULL);

}

void	*phil_sleeping(void *phil_num)
{
	int	*p;

	p = (int *)phil_num;
	ft_putstr_fd("philo ", 1);
	ft_putnbr_fd(*p, 1);
	ft_putstr_fd(" is sleeping...\n", 1);
    	return (NULL);

}

void	*phil_dead(void *phil_num)
{
	int	*p;

	p = (int *)phil_num;
	ft_putstr_fd("philo ", 1);
	ft_putnbr_fd(*p, 1);
	ft_putstr_fd(" is DEAD\n", 1);
    	return (NULL);

}