/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:22:41 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/16 22:12:38 by mstrauss         ###   ########.fr       */
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
		if (philo->id % 2 == 0 || philo->id == philo->philo_count)
			get_both_forks_even(philo);
		else if (philo->philo_count % 2 == 0)
			get_both_forks_odd(philo);
		pthread_mutex_lock(&philo->last_meal_time.mut);
		philo->last_meal_time.val = get_time_ms();
		announce(philo, get_run_time(philo), " is eating");
		pthread_mutex_unlock(&philo->last_meal_time.mut);
		better_sleep(philo->time_to_eat);
		if (philo->id % 2 == 0 || philo->id == philo->philo_count)
			return_both_forks_even(philo);
		else if (philo->philo_count % 2 == 0)
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
	wait_to_start(philo->start_time);
	think(philo);
	if (philo->id % 2 == 0 && philo->philo_count % 2 == 0)
		better_sleep(10);
	else if (philo->id % 2 != 0 && philo->philo_count % 2 == 0)
		better_sleep(0);
	else
		better_sleep(philo->id % 20);
}

bool	announce(t_philo *philo, uint_fast64_t time, char *msg)
{
	pthread_mutex_lock(&philo->stop->mut);
	if (philo->stop->val == true)
		return (pthread_mutex_unlock(&philo->stop->mut),
				/*return_all_locks(philo),*/ false);
	pthread_mutex_unlock(&philo->stop->mut);
	pthread_mutex_lock(&philo->speak_lck->mut);
	printf("%7" PRIu64 " %" PRIu64 "%s\n", time, philo->id, msg);
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
	if (philo->id % 2 == 0)
		usleep(500);
	return (announce(philo, get_run_time(philo), " is thinking"));
}
