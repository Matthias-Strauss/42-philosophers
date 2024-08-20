/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:18:24 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/20 19:52:06 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead_check(t_program *prog)
{
	uint8_t	i;
	t_philo	**tmp;
	uint8_t	amount;

	tmp = (t_philo **)prog->philos;
	while (1)
	{
		i = 0;
		while (i <= prog->amount)
		{
			if (check_vitals(tmp[i], prog))
			{
				prog->break ;
			}
			i++;
		}
		if (pthread_mutex_lock())
			break ;
	}
}

void	watcher(t_program *prog)
{
	;
}

bool	check_vitals(t_philo *philo, t_program *prog)
{
	pthread_mutex_lock(&philo->last_meal_time.mut);
	if ((philo->last_meal_time.val + philo->time_to_die) > get_time_ms())
	{
		pthread_mutex_lock(&prog->speak_lck.mut);
		prog->speak_lck.val = 2;
		pthread_mutex_unlock(&prog->speak_lck.mut);
		return (false);
	}
	return (true);
}
