/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:20:31 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/14 20:21:39 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* -------------------------------------------------------------------------- */
/*                                    PLAN                                    */
/* -------------------------------------------------------------------------- */
/*

LIMIT PICKING UP FORKS BY ONLY ALLOWING A SINGLE THREAD TO PICK UP FORKS
therefore making picking up 2 forks atomic, guaranteeing no deadlocks

- add mutex for PICKUP

+ check pthread_init attribute options
	- detach?
		Scheduling Policy: Specifies the scheduling policy for the thread.
		SCHED_OTHER (default): Default scheduling policy.
		SCHED_FIFO: First-in, first-out real-time scheduling policy.
		SCHED_RR: Round-robin real-time scheduling policy.

		Scheduling Parameters: Specifies the scheduling parameters for the thread (e.g.,
			priority).
		pthread_attr_setschedparam(&attr,
			&param): Sets the scheduling parameters.

			PTHREAD_SCOPE_PROCESS: The thread competes for resources with other threads in the same process.

*/

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_to_start(philo->start_time);
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat / 2); // TIME
	think(philo);
	while (!stop(philo))
	{
		if (philo->id % 2 == 0)
		{
			if (stop(philo) || !eat_even(philo))
				break ;
		}
		else
		{
			if (stop(philo) || !eat_odd(philo))
				break ;
		}
		if (!sleeep(philo))
			break ;
		if (!think(philo))
			break ;
	}
	return (NULL);
}

bool	eat_even(t_philo *philo)
{
	// while (!get_lock(WAITER, philo))
	// {
	// 	usleep(50); // TIME
	// }
	if (!get_lock(LEFT_FORK, philo))
		return (false);
	if (!announce(philo, get_rel_time(philo), " has taken a fork"))
		return (false);
	if (!get_lock(RIGHT_FORK, philo))
		return (false);
	if (!announce(philo, get_rel_time(philo), " has taken a fork"))
		return (false);
	// if (!return_lock(WAITER, philo))
	// 	return (printf("Philo %llu: eat() failed in line 81\n", philo->id),
	// 		false);
	return (consume_food(philo));
}

bool	eat_odd(t_philo *philo)
{
	// while (!get_lock(WAITER, philo))
	// {
	// 	usleep(50); // TIME
	// }
	if (!get_lock(RIGHT_FORK, philo))
		return (false);
	if (!announce(philo, get_rel_time(philo), " has taken a fork"))
		return (false);
	if (!get_lock(LEFT_FORK, philo))
		return (false);
	if (!announce(philo, get_rel_time(philo), " has taken a fork"))
		return (false);
	// if (!return_lock(WAITER, philo))
	// 	return (printf("Philo %llu: eat() failed in line 81\n", philo->id),
	// 		false);
	return (consume_food(philo));
}

bool	consume_food(t_philo *philo)
{
	uint64_t	time;
	uint64_t	timely_death;

	if (stop(philo))
		return (false);
	time = get_time_ms();
	get_lock(LAST_MEAL, philo);
	timely_death = philo->last_meal_time.val + philo->time_to_die;
	if (time >= timely_death)
		return (die(philo), false);
	// if (time + philo->time_to_eat >= timely_death)
	// {
	// 	wait_to_start(timely_death);
	// 	die(philo);
	// 	return (false);
	// }
	philo->last_meal_time.val = time;
	return_lock(LAST_MEAL, philo);
	announce(philo, time - philo->start_time, " is eating");
	better_sleep(philo->time_to_eat);
	return_lock(RIGHT_FORK, philo);
	return_lock(LEFT_FORK, philo);
	// printf("Philo %llu: new last_meal_time: %llu\n", philo->id,
	// 		philo->last_meal_time.val - philo->start_time); // DBG
	update_amount_eaten(philo);
	return (true);
}

bool	sleeep(t_philo *philo)
{
	uint64_t	time;
	uint64_t	timely_death;

	if (stop(philo))
		return (false);
	time = get_time_ms();
	get_lock(LAST_MEAL, philo);
	if (time >= philo->last_meal_time.val + philo->time_to_die)
		return (die(philo), false);
	timely_death = philo->last_meal_time.val + philo->time_to_die;
	return_lock(LAST_MEAL, philo);
	// if (time + philo->time_to_sleep >= timely_death)
	// {
	// 	wait_to_start(timely_death);
	// 	die(philo);
	// 	return (false);
	// }
	announce(philo, time - philo->start_time, " is sleeping");
	better_sleep(philo->time_to_sleep);
	return (true);
}

bool	think(t_philo *philo)
{
	if (stop(philo))
		return (false);
	announce(philo, get_rel_time(philo), " is thinking");
	return (true);
}

bool	announce(t_philo *philo, uint64_t time, char *msg)
{
	get_lock(SPEAK_LOCK, philo);
	get_lock(STOP, philo);
	if (philo->stop->val == true)
		return (return_all_locks(philo), false);
	printf("%7" PRIu64 " %" PRIu64 "%s\n", time, philo->id, msg);
	return_lock(STOP, philo);
	return_lock(SPEAK_LOCK, philo);
	return (true);
}

bool	stop(t_philo *philo)
{
	bool	status;

	get_lock(STOP, philo);
	status = philo->stop->val;
	return_lock(STOP, philo);
	return (status);
}

// add a function + mutex that allows anyone to take a break after thinking,
// except the philo that has taken the previous break