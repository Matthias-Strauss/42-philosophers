/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:18:24 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/16 23:15:23 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	watcher(t_program *prog)
{
	dead_check_loop(prog);
	kill_all(prog);
}

void	dead_check_loop(t_program *prog)
{
	uint_fast64_t	i;
	uint_fast64_t	least_eaten;
	uint_fast64_t	current_eaten;

	wait_to_start(prog->philos[0].start_time);
	while (true)
	{
		i = -1;
		least_eaten = UINT_FAST64_MAX;
		while (!stop_flag_raised(&prog->stop) && ++i < prog->amount)
		{
			current_eaten = get_amount_eaten(&prog->philos[i]);
			if (current_eaten < least_eaten)
				least_eaten = current_eaten;
			if (!check_starvation(&prog->philos[i], prog)
				|| stop_flag_raised(&prog->stop))
				return (raise_stop_flag(&prog->stop));
		}
		if (least_eaten >= prog->must_eat_amount)
		{
			raise_stop_flag(&prog->stop);
			return ;
		}
	}
}

bool	check_starvation(t_philo *philo, t_program *prog)
{
	pthread_mutex_lock(&philo->last_meal_time.mut);
	if (get_time_ms() >= (philo->last_meal_time.val + prog->time_to_die))
	{
		watcher_announce(philo, prog, "\033[0;31m died\033[0m");
		// DBG check if this is done doubly
		pthread_mutex_lock(&prog->stop.mut);
		prog->stop.val = true;
		pthread_mutex_unlock(&prog->stop.mut);
		pthread_mutex_unlock(&philo->last_meal_time.mut);
		return (false);
	}
	pthread_mutex_unlock(&philo->last_meal_time.mut);
	return (true);
}

void	raise_stop_flag(t_p_bool *stop_flag)
{
	pthread_mutex_lock(&stop_flag->mut);
	stop_flag->val = true;
	pthread_mutex_unlock(&stop_flag->mut);
}

bool	stop_flag_raised(t_p_bool *stop_flag)
{
	bool	status;

	pthread_mutex_lock(&stop_flag->mut);
	status = stop_flag->val;
	pthread_mutex_unlock(&stop_flag->mut);
	return (status);
}

void	kill_all(t_program *prog)
{
	unsigned int	i;

	i = 0;
	while (i < prog->amount)
	{
		pthread_mutex_lock(&((prog->philos)[i]).alive.mut);
		((prog->philos)[i]).alive.val = false;
		pthread_mutex_unlock(&((prog->philos)[i]).alive.mut);
		i++;
	}
}
