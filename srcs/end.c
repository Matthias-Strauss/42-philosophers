/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:10:15 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/16 22:10:24 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_muts(t_program *prog)
{
	unsigned int	i;

	i = 0;
	while (i < prog->amount)
	{
		pthread_mutex_destroy(&prog->forks[i].mut);
		pthread_mutex_destroy(&prog->philos[i].alive.mut);
		pthread_mutex_destroy(&prog->philos[i].last_meal_time.mut);
		i++;
	}
	pthread_mutex_destroy(&prog->speak_lck.mut);
	pthread_mutex_destroy(&prog->stop.mut);
}

void	rejoin_threads(t_program *prog)
{
	unsigned int	i;

	i = 0;
	while (i < prog->amount)
	{
		pthread_join(prog->threads[i], NULL);
		i++;
	}
}
