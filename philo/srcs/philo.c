/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:22:41 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/17 16:46:06 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	init_time_offsets(philo);
	while (carry_on(philo) == true)
	{
		get_both_forks_odd(philo);
		pthread_mutex_lock(&philo->last_meal_time.mut);
		philo->last_meal_time.val = get_time_ms();
		announce(philo, get_run_time(philo), " is eating");
		pthread_mutex_unlock(&philo->last_meal_time.mut);
		better_sleep(philo->time_to_eat);
		return_both_forks_odd(philo);
		increase_amount_eaten(philo);
		announce(philo, get_run_time(philo), " is sleeping");
		better_sleep(philo->time_to_sleep);
		announce(philo, get_run_time(philo), " is thinking");
	}
	return (NULL);
}

void	init_time_offsets(t_philo *philo)
{
	pthread_mutex_lock(&philo->start->mut);
	pthread_mutex_unlock(&philo->start->mut);
	set_last_meal_time(philo, *philo->start_time);
	think(philo);
	if (philo->id % 2 == 0)
		better_sleep(philo->time_to_eat / 2);
}

bool	announce(t_philo *philo, uint_fast64_t time, char *msg)
{
	pthread_mutex_lock(&philo->stop->mut);
	if (philo->stop->val == true)
		return (pthread_mutex_unlock(&philo->stop->mut), false);
	pthread_mutex_unlock(&philo->stop->mut);
	pthread_mutex_lock(&philo->speak_lck->mut);
	printf("%" PRIu64 " %" PRIu64 "%s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->speak_lck->mut);
	return (true);
}

bool	satiated(t_philo *philo)
{
	pthread_mutex_lock(&philo->amount_eaten.mut);
	if (philo->amount_eaten.val == philo->must_eat_amount)
	{
		pthread_mutex_unlock(&philo->amount_eaten.mut);
		return (true);
	}
	pthread_mutex_unlock(&philo->amount_eaten.mut);
	return (false);
}

bool	think(t_philo *philo)
{
	return (announce(philo, get_run_time(philo), " is thinking"));
}
