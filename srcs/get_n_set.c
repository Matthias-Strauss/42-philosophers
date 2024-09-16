/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_n_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:05:09 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/16 15:43:32 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
MUTEXES to account for:

	LEFT_FORK = 0,
	RIGHT_FORK = 1,
	SPEAK_LOCK = 2,
	LAST_MEAL = 3,
	AMOUNT_EATEN = 4,
	ALIVE = 5,
	STOP = 6,
*/

inline void	get_both_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	// philo->r_fork.val = 0; // ADD VALUE TOUCHING TO BE SUBJECT COMPLIANT
	announce(philo, get_run_time(philo), " has taken a fork");
	pthread_mutex_lock(philo->l_fork);
	// philo->l_fork.val = 0; // ADD VALUE TOUCHING TO BE SUBJECT COMPLIANT
	announce(philo, get_run_time(philo), " has taken a fork");
}

inline void	get_both_forks_even(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	// philo->l_fork.val = 0; // ADD VALUE TOUCHING TO BE SUBJECT COMPLIANT
	announce(philo, get_run_time(philo), " has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	// philo->r_fork.val = 0; // ADD VALUE TOUCHING TO BE SUBJECT COMPLIANT
	announce(philo, get_run_time(philo), " has taken a fork");
}

inline void	return_both_forks_odd(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

inline void	return_both_forks_even(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

inline void	get_l_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
}

inline void	get_r_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
}

inline void	get_voice(t_philo *philo)
{
	pthread_mutex_lock(&philo->speak_lck->mut);
}

inline void	return_voice(t_philo *philo)
{
	pthread_mutex_unlock(&philo->speak_lck->mut);
}

inline uint_fast64_t	get_last_meal_time(t_philo *philo)
{
	uint_fast64_t	time;

	pthread_mutex_lock(&philo->last_meal_time.mut);
	time = philo->last_meal_time.val;
	pthread_mutex_unlock(&philo->last_meal_time.mut);
	return (time);
}

inline void	set_last_meal_time(t_philo *philo, uint_fast64_t time)
{
	pthread_mutex_lock(&philo->last_meal_time.mut);
	philo->last_meal_time.val = time;
	pthread_mutex_unlock(&philo->last_meal_time.mut);
}

inline uint_fast64_t	get_amount_eaten(t_philo *philo)
{
	uint_fast64_t	amount;

	pthread_mutex_lock(&philo->amount_eaten.mut);
	amount = philo->amount_eaten.val;
	pthread_mutex_unlock(&philo->amount_eaten.mut);
	return (amount);
}

inline void	set_amount_eaten(t_philo *philo, uint_fast64_t amount)
{
	pthread_mutex_lock(&philo->amount_eaten.mut);
	philo->amount_eaten.val = amount;
	pthread_mutex_unlock(&philo->amount_eaten.mut);
}

inline void	increase_amount_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->amount_eaten.mut);
	philo->amount_eaten.val++;
	pthread_mutex_unlock(&philo->amount_eaten.mut);
}

inline bool	get_alive_val(t_philo *philo)
{
	bool	alive;

	pthread_mutex_lock(&philo->alive.mut);
	alive = philo->alive.val;
	pthread_mutex_unlock(&philo->alive.mut);
	return (alive);
}

inline void	set_alive_val(t_philo *philo, bool value)
{
	pthread_mutex_lock(&philo->alive.mut);
	philo->alive.val = value;
	pthread_mutex_unlock(&philo->alive.mut);
}

inline bool	carry_on(t_philo *philo)
{
	bool	value;

	pthread_mutex_lock(&philo->stop->mut);
	value = philo->stop->val;
	pthread_mutex_unlock(&philo->stop->mut);
	return (!value);
}

inline void	set_stop(t_philo *philo, bool stop)
{
	pthread_mutex_lock(&philo->stop->mut);
	philo->stop->val = stop;
	pthread_mutex_unlock(&philo->stop->mut);
}
