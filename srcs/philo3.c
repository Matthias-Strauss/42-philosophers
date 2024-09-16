/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 21:18:57 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/16 11:24:00 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	uint_fast64_t	time;

	philo = (t_philo *)arg;
	wait_to_start(philo->start_time);
	announce(philo, time = get_run_time(philo), " is thinking");
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat / 2);
	while (carry_on(philo))
	{
		if (request_forks(philo))
		{
			if (philo->id % 2 == 0)
				get_both_forks_even(philo);
			else
				get_both_forks_odd(philo);
			time = get_run_time(philo);
			announce(philo, get_run_time(philo), " is eating");
			better_sleep(philo->time_to_eat);
			if (philo->id % 2 == 0)
				return_both_forks_even(philo);
			else
				return_both_forks_odd(philo);
			set_last_meal_time(philo, time = get_time_ms());
			announce(philo, time = get_run_time(philo), " is sleeping");
			better_sleep(philo->time_to_sleep);
			announce(philo, time = get_run_time(philo), " is thinking");
		}
		else
			usleep(1000);
	}
	return (NULL);
}

/*
1234567 200 has taken a fork \
1234567 200 has taken a fork \
1234567 200 is eating
*/

/*
TODO

+ ADD BOOL TO WAITER STRUCT AND LOGIC TO request_forks() TO KNOW IF WE HAVE AN ODD TOTAL AMOUNT OF PHILOS
+ CALCULATE THE CORRECT COUNT DIFFERENT FOR EVEN AND ODD!!!!

+ HANDLE RETURN_ALL_LOCKS()!!!!!

- seperate routine into even and odd to save on if conditions
- change speak_lck to struct with val, block writing if a philo dies
- build routing for had_enough_meals()


- NORMINETTE
- FOLDER STRUCTURE ACCORDING TO SUBJECT
	-> Makefile adjustments

*/