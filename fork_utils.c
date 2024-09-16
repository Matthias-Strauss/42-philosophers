/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:44:52 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/16 20:45:20 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	get_both_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork->mut);
	philo->r_fork->val = 0;
	announce(philo, get_run_time(philo), " has taken a fork");
	pthread_mutex_lock(&philo->l_fork->mut);
	philo->l_fork->val = 0;
	announce(philo, get_run_time(philo), " has taken a fork");
}

inline void	get_both_forks_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->mut);
	philo->l_fork->val = 0;
	announce(philo, get_run_time(philo), " has taken a fork");
	pthread_mutex_lock(&philo->r_fork->mut);
	philo->r_fork->val = 0;
	announce(philo, get_run_time(philo), " has taken a fork");
}

inline void	return_both_forks_odd(t_philo *philo)
{
	philo->l_fork->val = 1;
	pthread_mutex_unlock(&philo->l_fork->mut);
	philo->r_fork->val = 1;
	pthread_mutex_unlock(&philo->r_fork->mut);
}

inline void	return_both_forks_even(t_philo *philo)
{
	philo->r_fork->val = 1;
	pthread_mutex_unlock(&philo->r_fork->mut);
	philo->l_fork->val = 1;
	pthread_mutex_unlock(&philo->l_fork->mut);
}
