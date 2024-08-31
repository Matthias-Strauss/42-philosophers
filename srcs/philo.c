/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:17:51 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/31 19:45:37 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Full philosophers routine per philosopher.
///			Each philosopher will cycle through:
///			- Eating
///			- Thinking
///			- Sleeping
/// @param philo the philosophers/threads variable struct
/// @param prog the main program struct
/// @return
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	set_mut_struct_uint64_t(&philo->last_meal_time, philo->start_time);
	wait_to_start(philo->start_time);
	// printf("last_meal_time set to: %" PRIu64 "\n",
	//	philo->last_meal_time.val);
	// printf("start_time     set to: %" PRIu64 "\n", philo->start_time);
	// printf("%" PRIu64 " is entering routine loop\n", philo->id); // DBG
	while (alive(philo))
	{
		// printf("%" PRIu64 " alive check passed\n", philo->id); // DBG
		if (p_acquire_utensils(philo))
		{
			if (alive(philo))
				p_eat(philo);
			p_return_utensils(philo);
			if (alive(philo))
				p_sleep(philo);
			if (alive(philo))
				p_think(philo);
		}
	}
	return (philo);
}

void	wait_to_start(uint64_t start_time)
{
	uint64_t	sleep_time;

	sleep_time = start_time - get_time_ms();
	if (sleep_time > 0)
	{
		// printf("Sleeping for: %" PRIu64 "(ms)\n", sleep_time); // DBG
		better_sleep(sleep_time);
	}
	else
		printf("ERROR: sleep time negative!\n"); // DBG
}

bool	p_acquire_utensils(t_philo *philo)
{
	if (philo->id % 2 != 0)
		return (get_r_fork(philo), announce(philo, " has taken a fork"),
			get_l_fork(philo), announce(philo, " has taken a fork"), true);
	else
		return (get_l_fork(philo), announce(philo, " has taken a fork"),
			get_r_fork(philo), announce(philo, " has taken a fork"), true);
}

void	p_return_utensils(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		return_l_fork(philo);
		return_r_fork(philo);
	}
	else
	{
		return_r_fork(philo);
		return_l_fork(philo);
	}
}

void	p_eat(t_philo *philo)
{
	announce(philo, " is eating");
	pthread_mutex_lock(&philo->last_meal_time.mut);
	philo->last_meal_time.val = get_time_ms();
	pthread_mutex_unlock(&philo->last_meal_time.mut);
	better_sleep(philo->time_to_eat);
}

void	p_sleep(t_philo *philo)
{
	announce(philo, " is sleeping");
	better_sleep(philo->time_to_sleep);
}

void	p_think(t_philo *philo)
{
	announce(philo, " is thinking");
}

bool	alive(t_philo *philo)
{
	uint64_t	time;

	if (stop_flag_raised(philo->stop))
		return (die(philo), false);
	pthread_mutex_lock(&philo->alive.mut);
	if (philo->alive.val == false)
	{
		printf("alive val neg, false returned\n"); // DBG
		pthread_mutex_unlock(&philo->alive.mut);
		return (false);
	}
	pthread_mutex_unlock(&philo->alive.mut);
	pthread_mutex_lock(&philo->last_meal_time.mut);
	time = get_time_ms();
	if (time >= (philo->last_meal_time.val + philo->time_to_die))
	{
		printf("Death by starvation triggered\n"); // DBG
		pthread_mutex_unlock(&philo->last_meal_time.mut);
		die(philo);
		return (false);
	}
	else
	{
		pthread_mutex_unlock(&philo->last_meal_time.mut);
		return (true);
	}
}

void	announce(t_philo *philo, /*uint64_t time,*/ char *msg)
{
	// uint64_t	time;
	pthread_mutex_lock(philo->speak_lck);
	printf("%" PRIu64 " %" PRIu64 "%s\n", get_time_ms(), philo->id, msg);
	// time = get_time_ms() - philo->start_time;
	// printf("%" PRIu64 " %" PRIu64 "%s\n", time, philo->id, msg);
	pthread_mutex_unlock(philo->speak_lck);
}

void	die(t_philo *philo)
{
	pthread_mutex_lock(&philo->alive.mut);
	philo->alive.val = false;
	pthread_mutex_unlock(&philo->alive.mut);
}
