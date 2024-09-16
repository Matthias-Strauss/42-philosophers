/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_timing_dependent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:22:41 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/16 12:45:47 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_to_start(philo->start_time);
	announce(philo, get_run_time(philo), " is thinking");
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat / 2 * 1000);
	usleep(philo->time_to_eat / 2 / philo->id * 1000);
	while (carry_on(philo))
	{
		if (philo->id % 2 == 0)
			get_both_forks_even(philo);
		else
			get_both_forks_odd(philo);
		announce(philo, get_run_time(philo), " is eating");
		better_sleep(philo->time_to_eat);
		set_last_meal_time(philo, get_time_ms());
		if (philo->id % 2 == 0)
			return_both_forks_even(philo);
		else
			return_both_forks_odd(philo);
		announce(philo, get_run_time(philo), " is sleeping");
		better_sleep(philo->time_to_sleep);
		announce(philo, get_run_time(philo), " is thinking");
	}
	return (NULL);
}
