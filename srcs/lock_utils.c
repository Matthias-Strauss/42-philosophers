/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:48:18 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/14 16:41:50 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	get_lock_continued(t_mutex_index mutex_index,
		t_philo *philo)
{
	static int	i = 0;

	if (mutex_index == AMOUNT_EATEN)
	{
		pthread_mutex_lock(&philo->amount_eaten.mut);
		philo->locks_held |= (1U << mutex_index);
		return (true);
	}
	else if (mutex_index == ALIVE)
	{
		pthread_mutex_lock(&philo->alive.mut);
		philo->locks_held |= (1U << mutex_index);
		return (true);
	}
	else if (mutex_index == STOP)
	{
		pthread_mutex_lock(&(philo->stop)->mut);
		philo->locks_held |= (1U << mutex_index);
		return (true);
	}
	else if (mutex_index == WAITER)
	{
		pthread_mutex_lock(&philo->waiter->mut);
		if (philo->id == philo->waiter->val + 1
			|| philo->id == philo->waiter->val - 1)
		{
			pthread_mutex_unlock(&philo->waiter->mut);
			printf("Philo %llu: rejected by WAITER\n", philo->id); // DBG
			i++;
			if (i > 100) // DBG
				exit(1);
			return (false);
		}
		else
		{
			philo->waiter->val = philo->id;
			philo->locks_held |= (1U << mutex_index);
			return (true);
		}
	}
	return (false);
}

/// @brief Dynamically gets a mutex lock corresponding to the calling thread,
///			and saves it in locks_held.
/// @param mutex_index enum of the mutex ment to be locked
/// @param philo the philosophers own data
/// @return true if lock has been taken, false if errors occured
bool	get_lock(t_mutex_index mutex_index, t_philo *philo)
{
	if (mutex_index == LEFT_FORK)
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
	else if (mutex_index == LAST_MEAL)
	{
		pthread_mutex_lock(&philo->last_meal_time.mut);
		philo->locks_held |= (1U << mutex_index);
		return (true);
	}
	return (get_lock_continued(mutex_index, philo));
}

/// @brief Returns a mutex lock held by the thread,
///			and updates the locks_held bitmap
/// @param mutex_index enum of the mutex ment to be return
/// @param philo the philo own data
/// @return
bool	return_lock(t_mutex_index mutex_index, t_philo *philo)
{
	if (!(philo->locks_held & (1U << mutex_index)))
	{
		printf("DBG: philo %llu ", philo->id);
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
	else if (mutex_index == ALIVE)
	{
		pthread_mutex_unlock(&philo->alive.mut);
		philo->locks_held &= ~(1U << mutex_index);
	}
	else if (mutex_index == STOP)
	{
		pthread_mutex_unlock(&philo->stop->mut);
		philo->locks_held &= ~(1U << mutex_index);
	}
	else if (mutex_index == WAITER)
	{
		philo->waiter->val = 202;
		pthread_mutex_unlock(&philo->waiter->mut);
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
