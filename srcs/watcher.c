/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:18:24 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/29 15:43:05 by mstrauss         ###   ########.fr       */
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
	unsigned int	i;
	unsigned int	amount;
	t_philo			*tmp;

	amount = prog->amount;
	while (!stop_flag_raised(prog))
	{
		tmp = prog->philos;
		i = 0;
		while (!stop_flag_raised(prog) && i < amount)
		{
			if (!check_vitals(&tmp[i], prog))
				break ;
			i++;
		}
	}
}

bool	check_vitals(t_philo *philo, t_program *prog)
{
	pthread_mutex_lock(&philo->last_meal_time.mut);
	if ((philo->last_meal_time.val + prog->time_to_die) > get_time_ms())
	{
		pthread_mutex_lock(&prog->stop.mut);
		prog->stop.val = true;
		pthread_mutex_unlock(&prog->stop.mut);
		pthread_mutex_unlock(&philo->last_meal_time.mut);
		return (false);
	}
	pthread_mutex_unlock(&philo->last_meal_time.mut);
	return (true);
}

bool	stop_flag_raised(t_program *prog)
{
	pthread_mutex_lock(&prog->stop.mut);
	if (prog->stop.val == true)
	{
		pthread_mutex_unlock(&prog->stop.mut);
		return (true);
	}
	else
		pthread_mutex_unlock(&prog->stop.mut);
	return (false);
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
