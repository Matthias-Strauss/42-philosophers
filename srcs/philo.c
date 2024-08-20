/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:17:51 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/20 21:01:21 by mstrauss         ###   ########.fr       */
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
void	*philo_routine(t_philo *philo, t_program *prog)
{
	while (alive(philo))
	{
		if (p_acquire_utensils(philo))
		{
			better_sleep(philo->time_to_sleep);
			p_sleep(philo);
			p_think(philo);
		}
	}
}

bool	p_acquire_utensils(t_philo *philo)
{
	if (get_fork(philo->l_fork) == true)
	{
		if (get_fork(philo->r_fork) == true)
			return (true);
		else
			return_fork(philo->l_fork);
		return (false);
	}
	else
		return (false);
}

void	p_sleep(t_philo *philo)
{
	better_sleep(philo->time_to_sleep);
}

void	p_think(t_philo *philo)
{
	pthread_mutex_lock();
	
}

bool	alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_time.mut);
	if (get_time_ms() <= (philo->last_meal_time.val + philo->time_to_die))
	{
		pthread_mutex_unlock(&philo->last_meal_time.mut);
		return (true);
	}
	pthread_mutex_unlock(&philo->last_meal_time.mut);
	return (false);
}
