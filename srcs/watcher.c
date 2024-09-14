/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:18:24 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/14 14:57:05 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	watcher(t_program *prog)
{
	printf("Time: %llu\n", get_time_ms()); // DBG
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
			if (!check_starvation(&tmp[i], prog)
				|| stop_flag_raised(&prog->stop))
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

void	watcher_announce(t_philo *philo, t_program *prog, char *msg)
{
	uint64_t	time;

	pthread_mutex_lock(&prog->speak_lck);
	time = get_time_ms() - philo->start_time;
	printf("%7" PRIu64 " %" PRIu64 "%s\n", time, philo->id, msg);
	pthread_mutex_unlock(&prog->speak_lck);
}
