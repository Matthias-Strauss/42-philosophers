/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_sleep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:12:37 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/03 16:56:02 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((uint64_t)time.tv_sec * (uint64_t)1000) + ((uint64_t)time.tv_usec
			/ (uint64_t)1000));
}

void	better_sleep(uint64_t ms)
{
	size_t	start;
	size_t	now;

	start = get_time_ms();
	while (1)
	{
		usleep(50);
		now = get_time_ms();
		if ((now - start) >= ms)
			break ;
	}
	return ;
}
