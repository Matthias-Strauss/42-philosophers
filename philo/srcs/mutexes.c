/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:59:00 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/17 18:07:51 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_philo_muts(t_program *prog, int start)
{
	while (start >= 0)
	{
		pthread_mutex_destroy(&prog->philos[start].alive.mut);
		pthread_mutex_destroy(&prog->philos[start].last_meal_time.mut);
		pthread_mutex_destroy(&prog->philos[start].amount_eaten.mut);
		pthread_mutex_destroy(&prog->forks[start].mut);
		start--;
	}
}

int	init_special_mutexes(t_program *prog)
{
	if (pthread_mutex_init(&prog->speak_lck.mut, NULL) != 0)
		return (destroy_philo_muts(prog, prog->amount - 1),
			printf("ERROR while initializing Mutex.\n"), 1);
	if (pthread_mutex_init(&prog->stop.mut, NULL) != 0)
		return (destroy_philo_muts(prog, prog->amount - 1),
			pthread_mutex_destroy(&prog->speak_lck.mut),
			printf("ERROR while initializing Mutex.\n"), 1);
	if (pthread_mutex_init(&prog->start.mut, NULL) != 0)
		return (destroy_philo_muts(prog, prog->amount - 1),
			pthread_mutex_destroy(&prog->speak_lck.mut),
			pthread_mutex_destroy(&prog->stop.mut),
			printf("ERROR while initializing Mutex.\n"), 1);
	return (0);
}

int	init_one_philo(t_program *prog, int i)
{
	if (pthread_mutex_init(&prog->forks[i].mut, NULL) != 0)
		return (printf("ERROR while initializing Mutex.\n"), 1);
	if (pthread_mutex_init(&prog->philos[i].alive.mut, NULL) != 0)
		return (pthread_mutex_destroy(&prog->forks[i].mut),
			printf("ERROR while initializing Mutex.\n"), 1);
	if (pthread_mutex_init(&prog->philos[i].last_meal_time.mut, NULL) != 0)
		return (pthread_mutex_destroy(&prog->forks[i].mut),
			pthread_mutex_destroy(&prog->philos[i].alive.mut),
			printf("ERROR while initializing Mutex.\n"), 1);
	if (pthread_mutex_init(&prog->philos[i].amount_eaten.mut, NULL) != 0)
		return (pthread_mutex_destroy(&prog->forks[i].mut),
			pthread_mutex_destroy(&prog->philos[i].alive.mut),
			pthread_mutex_destroy(&prog->philos[i].last_meal_time.mut),
			printf("ERROR while initializing Mutex.\n"), 1);
	return (0);
}

int	init_mutexs(t_program *prog)
{
	t_p_bool		*forks;
	unsigned int	i;

	i = 0;
	forks = prog->forks;
	while (i < prog->amount)
	{
		if (init_one_philo(prog, i))
		{
			destroy_philo_muts(prog, i - 1);
			return (1);
		}
		i++;
	}
	if (init_special_mutexes(prog))
		return (1);
	return (0);
}
