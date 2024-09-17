/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_n_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:12:37 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/17 16:24:00 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline uint_fast64_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

inline uint_fast64_t	get_run_time(t_philo *philo)
{
	return (get_time_ms() - *philo->start_time);
}

void	better_sleep(uint_fast64_t ms)
{
	uint_fast64_t	now;

	now = get_time_ms();
	while ((get_time_ms() - now) < ms)
	{
		usleep(500);
	}
	return ;
}

void	wait_to_start(uint_fast64_t start_time)
{
	uint_fast64_t	sleep_time;

	sleep_time = start_time - get_time_ms();
	if (sleep_time > 0)
	{
		better_sleep(sleep_time);
	}
}
