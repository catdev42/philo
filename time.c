/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myakoven <myakoven@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:40:59 by myakoven          #+#    #+#             */
/*   Updated: 2024/11/22 03:53:20 by myakoven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Returns 0 on error */
uint64_t	get_time(void)
{
	struct timeval timev;

	if (gettimeofday(&timev, NULL))
		return (0);
	return (timev.tv_sec * (uint64_t)1000 + timev.tv_usec / (uint64_t)1000);
}
int precise_sleep(uint64_t sleep_time)
{
    uint64_t start_time;
    uint64_t end_time;
    start_time = get_time();
    end_time= 
}
