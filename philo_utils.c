/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:07:23 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/20 20:59:50 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_fork(t_p_bool *fork)
{
	pthread_mutex_lock(&fork->mut);
	if (fork->val == true)
	{
		fork->val == false;
		pthread_mutex_unlock(&fork->mut);
		return (true);
	}
	else
		pthread_mutex_unlock(&fork->mut);
	return (false);
}

bool	return_fork(t_p_bool *fork)
{
	pthread_mutex_lock(&fork->mut);
	if (fork->val == true)
	{
		printf("ERROR: fork duplication!\n fork_bool non zero when returning\
			fork\n");
		exit(3);
	}
	else
	{
		fork->val = true;
		pthread_mutex_unlock(&fork->mut);
	}
	return (true);
}

uint8_t	get_voice(t_p_uint *speak_lck)
{
	pthread_mutex_lock(&speak_lck->mut);
	if (speak_lck->val == 2)
	{
		pthread_mutex_unlock(&speak_lck->mut);
		return (2);
		// CHECK IF I CAN EXIT() HERE.
		// probably not because of other mutexes
	}
	else if (speak_lck->val == 1)
	{
		speak_lck->val == 0;
		pthread_mutex_unlock(&speak_lck->mut);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&speak_lck->mut);
		return (0);
	}
}

uint8_t	return_voice(t_p_uint *speak_lck)
{
	pthread_mutex_lock(&speak_lck->mut);
	if (speak_lck->val == 2)
	{
		pthread_mutex_unlock(&speak_lck->mut);
		return (2);
		// CHECK IF I CAN EXIT() HERE.
		// probably not because of other mutexes
	}
	else if (speak_lck->val == 1)
	{
		speak_lck->val == 0;
		pthread_mutex_unlock(&speak_lck->mut);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&speak_lck->mut);
		return (0);
	}
}
