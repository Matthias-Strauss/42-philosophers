/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:50:39 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/16 16:31:17 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *philo)
{
	set_alive_val(philo, false);
	// announce(philo, "\033[0;31m died\033[0m");
	raise_stop_flag(philo->stop);
	return_all_locks(philo);
}

void	update_amount_eaten(t_philo *philo)
{
	uint_fast64_t	amount;

	pthread_mutex_lock(&philo->amount_eaten.mut);
	amount = ++philo->amount_eaten.val;
	pthread_mutex_unlock(&philo->amount_eaten.mut);
	// if (amount == philo->must_eat_amount)
	// 	raise_stop_flag(philo->stop); // ALL PHILOS MUST FINISH EATING
}

bool	return_all_locks(t_philo *philo)
{
	(void)philo;
	return (true); // PLACEHOLDER 11!11!!!!!!!!!!
}

/* -------------------------------------------------------------------------- */
/*                                 DEPRECATED                                 */
/* -------------------------------------------------------------------------- */
/*
{
	if (philo->locks_held & (1U << LEFT_FORK))
	{
		pthread_mutex_unlock(philo->l_fork);
		philo->locks_held &= ~(1U << LEFT_FORK);
	}
	if (philo->locks_held & (1U << RIGHT_FORK))
	{
		pthread_mutex_unlock(philo->r_fork);
		philo->locks_held &= ~(1U << RIGHT_FORK);
	}
	if (philo->locks_held & (1U << SPEAK_LOCK))
	{
		pthread_mutex_unlock(philo->speak_lck);
		philo->locks_held &= ~(1U << SPEAK_LOCK);
	}
	if (philo->locks_held & (1U << LAST_MEAL))
	{
		pthread_mutex_unlock(&philo->last_meal_time.mut);
		philo->locks_held &= ~(1U << LAST_MEAL);
	}
	if (philo->locks_held & (1U << AMOUNT_EATEN))
	{
		pthread_mutex_unlock(&philo->amount_eaten.mut);
		philo->locks_held &= ~(1U << AMOUNT_EATEN);
	}
	if (philo->locks_held & (1U << ALIVE))
	{
		pthread_mutex_unlock(&philo->alive.mut);
		philo->locks_held &= ~(1U << ALIVE);
	}
	if (philo->locks_held & (1U << STOP))
	{
		pthread_mutex_unlock(&philo->stop->mut);
		philo->locks_held &= ~(1U << STOP);
	}
	if (philo->locks_held & (1U << WAITER))
	{
		philo->waiter->val = 202;
		pthread_mutex_unlock(&philo->waiter->mut);
		philo->locks_held &= ~(1U << WAITER);
	}
	return (true);
}
*/