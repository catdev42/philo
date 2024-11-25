/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:28:10 by myakoven          #+#    #+#             */
/*   Updated: 2024/11/25 03:09:22 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// # include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct magic
{
	int		i;
}			t_magic;

uint64_t	get_time(void);

/*****ACTIONS_C******/
void		*phil_eating(void *phil_num);
void		*phil_thinking(void *phil_num);
void		*phil_sleeping(void *phil_num);
void		*phil_dead(void *phil_num);

/*****MINILIB_C******/
void		ft_putchar_fd(char c, int fd);

void		ft_putstr_fd(const char *s, int fd);

void		ft_putnbr_fd(int n, int fd);

#endif