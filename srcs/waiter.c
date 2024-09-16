/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:11:45 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/16 11:09:55 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// group: 0 = even, 1 = odd

// bool	request_forks(t_philo *philo)
// {
// 	static bool			group;
// 	static bool			skip;
// 	static uint_fast8_t	count;

// 	if ((philo->id & 1) == group)
// 	{
// 		if (philo->id == 1 && skip)
// 			return (skip = !skip, false);
// 		else if (philo->id == philo->philo_count && !skip)
// 			return (skip = !skip, false);
// 		if (++count == philo->philo_count / 2)
// 		{
// 			group = !group;
// 			count = 0;
// 		}
// 		return (true);
// 	}
// 	else
// 		return (false);
// }

bool	request_forks(t_philo *philo)
{
	t_waiter	*waiter;

	waiter = philo->waiter;
	pthread_mutex_lock(&waiter->mut);
	if ((philo->id & 1) == waiter->group)
	{
		if (waiter->group)
		{
			if (!waiter->someone_skipped && philo->id != waiter->last_skipper)
			{
				waiter->someone_skipped = true;
				waiter->last_skipper = philo->id;
				return (pthread_mutex_unlock(&waiter->mut), printf("%7llu Philo %llu is SKIPPING\n", get_run_time(philo), philo->id), false);
			}
			if (waiter->someone_skipped && philo->id == waiter->last_skipper) // ESSENTIAL!!! NEEDS A CONDITION FOR IF THE ROUND HAS CHANGED, otherwise the last skipper skips over and over that round, until someone else comes before him
				return (pthread_mutex_unlock(&waiter->mut),printf("%7llu Philo %llu rejected again\n", get_run_time(philo), philo->id), false);
		}
		if (++waiter->count == (philo->philo_count) / 2 /*+ waiter->group*/) // odd - skipper = even , except when TOTAL is even
		{
			waiter->group = !waiter->group;
			waiter->someone_skipped = false;
			waiter->count = 0;
		}
		return (pthread_mutex_unlock(&waiter->mut), true);
	}
	return (pthread_mutex_unlock(&waiter->mut), false);
}

/*

--------------------------------------------------------------------------
								POLICY DEFINITION
--------------------------------------------------------------------------

5 Philosophers:
----------------

1 2 3 4 5
  *   *

1 2 3 4 5
*   *

1 2 3 4 5
  *   *

1 2 3 4 5
	*   *

~ Repeat ~
*/