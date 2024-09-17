/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:54:21 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/17 17:23:32 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	watcher_announce(t_philo *philo, t_program *prog, char *msg)
{
	uint_fast64_t	time;

	pthread_mutex_lock(&prog->speak_lck.mut);
	time = get_time_ms() - *philo->start_time;
	printf("%" PRIu64 " %" PRIu64 "%s\n", time, philo->id, msg);
	pthread_mutex_unlock(&prog->speak_lck.mut);
}

void	kill_all(t_program *prog)
{
	unsigned int	i;

	i = 0;
	while (i < prog->amount)
	{
		pthread_mutex_lock(&((prog->philos)[i]).alive.mut);
		((prog->philos)[i]).alive.val = false;
		pthread_mutex_unlock(&((prog->philos)[i]).alive.mut);
		i++;
	}
}
