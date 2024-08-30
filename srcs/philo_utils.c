/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:07:23 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/30 12:52:14 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_l_fork(t_philo *philo)
{
	return (get_fork(philo->l_fork), true);
}

bool	get_r_fork(t_philo *philo)
{
	return (get_fork(philo->r_fork), true);
}

bool	get_fork(pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	return (true);
}

bool	return_fork(pthread_mutex_t *fork)
{
	return (pthread_mutex_unlock(fork), true);
}

bool	return_l_fork(t_philo *philo)
{
	return (return_fork(philo->l_fork));
}

bool	return_r_fork(t_philo *philo)
{
	return (return_fork(philo->r_fork));
}

bool	get_voice(t_philo *philo)
{
	return (pthread_mutex_lock(philo->speak_lck), true);
}

bool	return_voice(t_philo *philo)
{
	return (pthread_mutex_unlock(philo->speak_lck), true);
}
