/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:18:24 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/31 18:53:18 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	watcher(t_program *prog)
{
	printf("Watcher entering DeathCheckLoop\n"); // DBG
	dead_check_loop(prog);
	printf("Watcher entering Kill_All\n"); // DBG
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
			if (!check_vitals(&tmp[i], prog))
			{
				raise_stop_flag(&prog->stop);
				break ;
			}
			i++;
		}
	}
}

bool	check_vitals(t_philo *philo, t_program *prog)
{
	pthread_mutex_lock(&philo->last_meal_time.mut);
	if ((philo->last_meal_time.val + prog->time_to_die) < get_time_ms())
	{
		// printf("%" PRIu64 " died in CHECK_VITALS (watcher) because of time\n",
		// philo->id); // DBG
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
	pthread_mutex_lock(&stop_flag->mut);
	if (stop_flag->val == true)
	{
		pthread_mutex_unlock(&stop_flag->mut);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&stop_flag->mut);
		return (false);
	}
}

void	raise_stop_flag(t_p_bool *stop_flag)
{
	pthread_mutex_lock(&stop_flag->mut);
	stop_flag->val = true;
	pthread_mutex_unlock(&stop_flag->mut);
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
