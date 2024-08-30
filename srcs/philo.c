/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:17:51 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/30 12:50:36 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Full philosophers routine per philosopher.
///			Each philosopher will cycle through:
///			- Eating
///			- Thinking
///			- Sleeping
/// @param philo the philosophers/threads variable struct
/// @param prog the main program struct
/// @return
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	announce(philo, get_time_ms(), "thread started\n"); // DBG
	while (alive(philo))
	{
		if (p_acquire_utensils(philo))
		{
			p_eat(philo);
			p_return_utensils(philo);
			p_sleep(philo);
			p_think(philo);
		}
	}
	return (philo);
}

bool	p_acquire_utensils(t_philo *philo)
{
	if (philo->id % 2 != 0)
		return (get_r_fork(philo), announce(philo, get_time_ms(),
				"X has taken a fork\n"), get_l_fork(philo), announce(philo,
				get_time_ms(), "X has taken a fork\n"), true);
	else
		return (get_l_fork(philo), announce(philo, get_time_ms(),
				"X has taken a fork\n"), get_r_fork(philo), announce(philo,
				get_time_ms(), "X has taken a fork\n"), true);
}

void	p_return_utensils(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		return_l_fork(philo);
		return_r_fork(philo);
	}
	else
	{
		return_r_fork(philo);
		return_l_fork(philo);
	}
}

void	p_eat(t_philo *philo)
{
	announce(philo, get_time_ms(), "is eating\n");
	better_sleep(philo->time_to_eat);
}

void	p_sleep(t_philo *philo)
{
	announce(philo, get_time_ms(), "is sleeping\n");
	better_sleep(philo->time_to_sleep);
}

void	p_think(t_philo *philo)
{
	announce(philo, get_time_ms(), "is thinking\n");
}

bool	alive(t_philo *philo)
{
	unsigned int	time;

	// Death through Watcher
	pthread_mutex_lock(&philo->alive.mut);
	if (philo->alive.val == false)
		return (pthread_mutex_unlock(&philo->alive.mut), false);
	pthread_mutex_unlock(&philo->alive.mut);
	// Death through TIMEOUT
	pthread_mutex_lock(&philo->last_meal_time.mut);
	time = get_time_ms();
	if (time <= (philo->last_meal_time.val + philo->time_to_die))
	{
		pthread_mutex_unlock(&philo->last_meal_time.mut);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&philo->last_meal_time.mut);
		die(philo);
		return (false);
	}
}

void	announce(t_philo *philo, long time, char *msg)
{
	get_voice(philo);
	printf("%ld %d %s\n", time, philo->id, msg);
	return_voice(philo);
}

void	die(t_philo *philo)
{
	pthread_mutex_lock(&philo->alive.mut);
	philo->alive.val = false;
	pthread_mutex_unlock(&philo->alive.mut);
}
