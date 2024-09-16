/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:35:22 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/15 23:14:12 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// /// @brief Full philosophers routine per philosopher.
// ///			Each philosopher will cycle through:
// ///			- Eating
// ///			- Thinking
// ///			- Sleeping
// /// @param philo the philosophers/threads variable struct
// /// @param prog the main program struct
// /// @return
// // void	*philo_routine(void *arg)
// // {
// // 	t_philo	*philo;

// // 	philo = (t_philo *)arg;
// // 	// set_mut_struct_uint_fast64_t(&philo->last_meal_time,
// philo->start_time);
// // 	wait_to_start(philo->start_time);
// // 	p_think(philo);
// // 	if (philo->id % 2 != 0)
// // 		usleep(philo->time_to_eat - 10);
// // 	// printf("last_meal_time set to: %" PRIu64 "\n",
// // 	// philo->last_meal_time.val);
// // 	// printf("start_time     set to: %" PRIu64 "\n", philo->start_time);
// // 	// printf("%" PRIu64 " is entering routine loop\n", philo->id); // DBG
// // 	while (alive(philo) && !stop_flag_raised(philo->stop))
// // 	{
// // 		// printf("%" PRIu64 " alive check passed\n", philo->id); // DBG
// // 		if (p_acquire_utensils(philo) && !stop_flag_raised(philo->stop))
// // 		{
// // 			if (alive(philo) && !stop_flag_raised(philo->stop))
// // 				p_eat(philo);
// // 			p_return_utensils(philo);
// // 			if (alive(philo) && !stop_flag_raised(philo->stop))
// // 				p_sleep(philo);
// // 			if (alive(philo) && !stop_flag_raised(philo->stop))
// // 				p_think(philo);
// // 		}
// // 	}
// // 	die(philo);
// // 	return (philo);
// // }

// bool	p_acquire_utensils(t_philo *philo)
// {
// 	// if (philo->id % 2 != 0)
// 	// {
// 	// 	get_lock(LEFT_FORK, philo);
// 	// 	announce(philo, " has taken a fork");
// 	// 	get_lock(RIGHT_FORK, philo);
// 	// 	announce(philo, " has taken a fork");
// 	// 	return (true);
// 	// }
// 	// else
// 	// {
// 	// 	get_lock(RIGHT_FORK, philo);
// 	// 	announce(philo, " has taken a fork");
// 	// 	get_lock(LEFT_FORK, philo);
// 	// 	announce(philo, " has taken a fork");
// 	// 	return (true);
// 	// }
// 	if (philo->id == philo->philo_count - 1)
// 	{
// 		get_lock(LEFT_FORK, philo);
// 		announce(philo, " has taken a fork");
// 		get_lock(RIGHT_FORK, philo);
// 		announce(philo, " has taken a fork");
// 	}
// 	else
// 	{
// 		get_lock(RIGHT_FORK, philo);
// 		announce(philo, " has taken a fork");
// 		get_lock(LEFT_FORK, philo);
// 		announce(philo, " has taken a fork");
// 	}
// 	return (true);
// }

// void	p_return_utensils(t_philo *philo)
// {
// 	// if (philo->id % 2 != 0)
// 	// {
// 	// 	return_lock(RIGHT_FORK, philo);
// 	// 	return_lock(LEFT_FORK, philo);
// 	// }
// 	// else
// 	// {
// 	// 	return_lock(LEFT_FORK, philo);
// 	// 	return_lock(RIGHT_FORK, philo);
// 	// }
// 	if (philo->id == philo->philo_count - 1)
// 	{
// 		return_lock(LEFT_FORK, philo);
// 		announce(philo, " has taken a fork");
// 		return_lock(RIGHT_FORK, philo);
// 		announce(philo, " has taken a fork");
// 	}
// 	else
// 	{
// 		return_lock(RIGHT_FORK, philo);
// 		announce(philo, " has taken a fork");
// 		return_lock(LEFT_FORK, philo);
// 		announce(philo, " has taken a fork");
// 	}
// }

// void	p_eat(t_philo *philo)
// {
// 	uint_fast64_t	time;

// 	announce(philo, " is eating");
// 	get_lock(LAST_MEAL, philo);
// 	time = get_time_ms(); // ADJUST WHEN WE GET TIME
// 	if (time >= (philo->last_meal_time.val + philo->time_to_die))
// 	{
// 		return_lock(LAST_MEAL, philo);
// 		die(philo);
// 		return ;
// 	}
// 	philo->last_meal_time.val = time;
// 	return_lock(LAST_MEAL, philo);
// 	better_sleep(philo->time_to_eat); // MAYBE REVERSE ORDERS????
// 	update_amount_eaten(philo);
// }

// void	p_sleep(t_philo *philo)
// {
// 	announce(philo, " is sleeping");
// 	better_sleep(philo->time_to_sleep);
// }

// void	p_think(t_philo *philo)
// {
// 	if (philo->id % 2 != 0) // RESYNC GROUPS
// 		usleep(100);
// 	announce(philo, " is thinking");
// }

// // bool	alive(t_philo *philo)
// // {
// // 	uint_fast64_t	time;

// // 	if (stop_flag_raised(philo->stop))
// // 		return (die(philo), false);
// // 	get_lock(ALIVE, philo);
// // 	if (philo->alive.val == false)
// // 	{
// // 		// printf("alive val neg, false returned\n"); // DBG
// // 		return_lock(ALIVE, philo);
// // 		return (false);
// // 	}
// // 	return_lock(ALIVE, philo);
// // 	get_lock(LAST_MEAL, philo);
// // 	time = get_time_ms();
// // 	if (time >= (philo->last_meal_time.val + philo->time_to_die))
// // 	{
// // 		announce(philo, "\033[0;31m died\033[0m");
// // 		// return_lock(LAST_MEAL, philo);
// // 		die(philo);
// // 		return (false);
// // 	}
// // 	else
// // 	{
// // 		return_lock(LAST_MEAL, philo);
// // 		return (true);
// // 	}
// // }

// // void	announce(t_philo *philo, /*uint_fast64_t time,*/ char *msg)
// // {
// // 	uint_fast64_t	time;

// // 	time = get_time_ms() - philo->start_time;
// // 	get_lock(SPEAK_LOCK, philo);
// // 	// printf("%" PRIu64 " %" PRIu64 "%s\n", get_time_ms(), philo->id, msg);
// // 	if (!stop_flag_raised(philo->stop))
// // 		printf("%" PRIu64 " %" PRIu64 "%s\n", time, philo->id, msg);
// // 	return_lock(SPEAK_LOCK, philo);
// // }

// void	die(t_philo *philo)
// {
// 	get_lock(ALIVE, philo);
// 	philo->alive.val = false;
// 	// announce(philo, "\033[0;31m died\033[0m");
// 	return_lock(ALIVE, philo);
// 	raise_stop_flag(philo->stop);
// 	return_all_locks(philo);
// }

// void	update_amount_eaten(t_philo *philo)
// {
// 	uint_fast64_t	amount;

// 	get_lock(AMOUNT_EATEN, philo);
// 	// philo->amount_eaten.val += 1;
// 	amount = ++philo->amount_eaten.val;
// 	return_lock(AMOUNT_EATEN, philo);
// 	if (amount == philo->must_eat_amount)
// 		raise_stop_flag(philo->stop); // ALL PHILOS MUST FINISH EATING
// }

// // NEEDS TO EXIT ONLY IF ALL HAVE EATEN
