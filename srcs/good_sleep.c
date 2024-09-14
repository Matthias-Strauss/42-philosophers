/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_sleep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:12:37 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/14 19:40:22 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((uint64_t)time.tv_sec * 1000) + ((uint64_t)time.tv_usec / 1000));
}

uint64_t	get_rel_time(t_philo *philo)
{
	return (get_time_ms() - philo->start_time);
}

void	better_sleep(uint64_t ms)
{
	uint64_t	start;
	uint64_t	now;

	start = get_time_ms();
	if (ms > 10)
		usleep((ms - 5) * 1000);
	now = get_time_ms();
	while ((now - start) <= ms)
	{
		usleep(50);
		now = get_time_ms();
	}
	return ;
}
