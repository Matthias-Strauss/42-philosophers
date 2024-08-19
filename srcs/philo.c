/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:17:51 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/19 14:52:58 by mstrauss         ###   ########.fr       */
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
void	*philo_routine(t_philo *philo, t_program *prog)
{
	while (!prog->stop) // replace with function
	{
		if (eat() == 1)
		{
			slep();
			think();
		}
	}
}

int	p_eat(void)
{
}

int	p_sleep(t_philo *philo)
{
	better_sleep(philo->time_to_sleep);
}

int	p_think(void)
{
}

bool	unalive(t_philo *philo)
{
	if (get_time_ms(philo) >= (philo->last_meal_time + philo->time_to_die))
		return (true);
	return (false);
}
