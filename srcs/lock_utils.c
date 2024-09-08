/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:48:18 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/08 15:13:27 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	get_lock_continued(t_mutex_index mutex_index,
		t_philo *philo)
{
	if (mutex_index == LAST_MEAL)
	{
		pthread_mutex_lock(&philo->last_meal_time.mut);
		philo->locks_held |= (1U << mutex_index);
		return (true);
	}
	else if (mutex_index == AMOUNT_EATEN)
	{
		pthread_mutex_lock(&philo->amount_eaten.mut);
		philo->locks_held |= (1U << mutex_index);
		return (true);
	}
	else
		return (false);
}

/// @brief Dynamically gets a mutex lock corresponding to the calling thread,
///			and saves it in locks_held.
/// @param mutex_index
/// @param philo
/// @return
bool	get_lock(t_mutex_index mutex_index, t_philo *philo)
{
	if (philo->locks_held & (1U << mutex_index))
	{
		printf("Error: Lock is already held\n");
		return (false);
	}
	else if (mutex_index == LEFT_FORK)
	{
		pthread_mutex_lock(philo->l_fork);
		philo->locks_held |= (1U << mutex_index);
		return (true);
	}
	else if (mutex_index == RIGHT_FORK)
	{
		pthread_mutex_lock(philo->r_fork);
		philo->locks_held |= (1U << mutex_index);
		return (true);
	}
	else if (mutex_index == SPEAK_LOCK)
	{
		pthread_mutex_lock(philo->speak_lck);
		philo->locks_held |= (1U << mutex_index);
		return (true);
	}
	return (get_lock_continued(mutex_index, philo));
}

bool	return_lock(t_mutex_index mutex_index, t_philo *philo)
{
	if (!(philo->locks_held & (1U << mutex_index)))
	{
		printf("Error: Lock being returned isn't held in the first place\n");
		return (false);
	}
	else if (mutex_index == LEFT_FORK)
	{
		pthread_mutex_unlock(philo->l_fork);
		philo->locks_held &= ~(1U << mutex_index);
	}
	else if (mutex_index == RIGHT_FORK)
	{
		pthread_mutex_unlock(philo->r_fork);
		philo->locks_held &= ~(1U << mutex_index);
	}
	else if (mutex_index == SPEAK_LOCK)
	{
		pthread_mutex_unlock(philo->speak_lck);
		philo->locks_held &= ~(1U << mutex_index);
	}
	else if (mutex_index == LAST_MEAL)
	{
		pthread_mutex_unlock(&philo->last_meal_time.mut);
		philo->locks_held &= ~(1U << mutex_index);
	}
	else if (mutex_index == AMOUNT_EATEN)
	{
		pthread_mutex_unlock(&philo->amount_eaten.mut);
		philo->locks_held &= ~(1U << mutex_index);
	}
	return (true);
}

bool	return_all_locks(t_philo *philo)
{
	if (philo->locks_held & (1U << LEFT_FORK))
	{
		pthread_mutex_unlock(philo->l_fork);
		philo->locks_held &= ~(1U << LEFT_FORK);
	}
	else
		printf("Error: Attempting to return_LEFT_FORK which is not held\n");
	if (philo->locks_held & (1U << RIGHT_FORK))
	{
		pthread_mutex_unlock(philo->r_fork);
		philo->locks_held &= ~(1U << RIGHT_FORK);
	}
	else
		printf("Error: Attempting to return_RIGHT_FORK which is not held\n");
	if (philo->locks_held & (1U << SPEAK_LOCK))
	{
		pthread_mutex_unlock(philo->speak_lck);
		philo->locks_held &= ~(1U << SPEAK_LOCK);
	}
	else
		printf("Error: Attempting to return_SPEAK_LOCK which is not held\n");
	if (philo->locks_held & (1U << LAST_MEAL))
	{
		pthread_mutex_unlock(&philo->last_meal_time.mut);
		philo->locks_held &= ~(1U << LAST_MEAL);
	}
	else
		printf("Error: Attempting to return_LAST_MEAL which is not held\n");
	if (philo->locks_held & (1U << AMOUNT_EATEN))
	{
		pthread_mutex_unlock(&philo->amount_eaten.mut);
		philo->locks_held &= ~(1U << AMOUNT_EATEN);
	}
	else
		printf("Error: Attempting to return_AMOUNT_EATEN which is not held\n");
	return (true);
}
