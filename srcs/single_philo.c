/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:25:23 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/14 11:29:28 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_mut_struct_uint64_t(&philo->last_meal_time, philo->start_time);
	wait_to_start(philo->start_time);
	get_lock(LEFT_FORK, philo);
	announce(philo, get_time_ms(), " has taken a fork");
	better_sleep(philo->time_to_die);
	announce(philo, get_time_ms(), "\033[0;31m died\033[0m");
	die(philo);
	return (philo);
}
