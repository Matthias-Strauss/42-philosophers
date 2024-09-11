/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:18:24 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/11 18:58:57 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	watcher(t_program *prog)
{
	// printf("Watcher entering DeathCheckLoop\n"); // DBG
	dead_check_loop(prog);
	// printf("Watcher entering Kill_All\n"); // DBG
	kill_all(prog);
}

void	dead_check_loop(t_program *prog)
{
	uint64_t	i;
	uint64_t	amount;
	t_philo		*tmp;

	amount = prog->amount;
	tmp = prog->philos;
	wait_to_start(prog->philos[0].start_time);
	while (!stop_flag_raised(&prog->stop))
	{
		i = 0;
		while (!stop_flag_raised(&prog->stop) && i < amount)
		{
			if (!check_starvation(&tmp[i], prog))
			{
				raise_stop_flag(&prog->stop);
				break ;
			}
			i++;
		}
	}
}

bool	check_starvation(t_philo *philo, t_program *prog)
{
	pthread_mutex_lock(&philo->last_meal_time.mut);
	if (get_time_ms() >= (philo->last_meal_time.val + prog->time_to_die))
	{
		announce(philo, " died"); // DBG check if this is done doubly
		pthread_mutex_lock(&prog->stop.mut);
		prog->stop.val = true;
		pthread_mutex_unlock(&prog->stop.mut);
		pthread_mutex_unlock(&philo->last_meal_time.mut);
		return (false);
	}
	pthread_mutex_unlock(&philo->last_meal_time.mut);
	return (true);
}

bool	stop_flag_raised(t_p_bool *stop_flag)
{
	bool	status;

	pthread_mutex_lock(&stop_flag->mut);
	status = stop_flag->val;
	pthread_mutex_unlock(&stop_flag->mut);
	return (status);
}

void	raise_stop_flag(t_p_bool *stop_flag)
{
	set_mut_struct_bool(stop_flag, true);
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
