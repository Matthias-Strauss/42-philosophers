/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 22:50:39 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/17 14:21:33 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *philo)
{
	set_alive_val(philo, false);
	set_stop(philo, false);
}

uint_fast64_t	update_amount_eaten(t_philo *philo)
{
	uint_fast64_t	amount;

	pthread_mutex_lock(&philo->amount_eaten.mut);
	amount = ++philo->amount_eaten.val;
	pthread_mutex_unlock(&philo->amount_eaten.mut);
	return (amount);
}

uint_fast64_t	increase_amount_eaten(t_philo *philo)
{
	uint_fast64_t	amount;

	pthread_mutex_lock(&philo->amount_eaten.mut);
	amount = philo->amount_eaten.val++;
	pthread_mutex_unlock(&philo->amount_eaten.mut);
	return (amount);
}
