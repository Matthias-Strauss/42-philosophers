/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:25:23 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/17 17:22:04 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->start->mut);
	pthread_mutex_unlock(&philo->start->mut);
	set_last_meal_time(philo, *philo->start_time);
	pthread_mutex_lock(&philo->l_fork->mut);
	philo->l_fork->val = 0;
	pthread_mutex_unlock(&philo->l_fork->mut);
	announce(philo, get_run_time(philo), " has taken a fork");
	better_sleep(philo->time_to_die);
	announce(philo, get_time_ms(), "\033[0;31m died\033[0m");
	die(philo);
	return (philo);
}
