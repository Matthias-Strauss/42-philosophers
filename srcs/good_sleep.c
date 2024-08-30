/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_sleep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:12:37 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/30 12:45:45 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000 + (long)time.tv_usec / 1000);
}

void	better_sleep(size_t ms)
{
	size_t	start;
	size_t	now;

	start = get_time_ms();
	while (1)
	{
		usleep(50);
		now = get_time_ms();
		if ((now - start) < ms)
			break ;
	}
	return ;
}
