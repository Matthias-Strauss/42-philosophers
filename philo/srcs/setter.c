/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:48:12 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/17 14:56:48 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	return_voice(t_philo *philo)
{
	pthread_mutex_unlock(&philo->speak_lck->mut);
}

void	set_last_meal_time(t_philo *philo, uint_fast64_t time)
{
	pthread_mutex_lock(&philo->last_meal_time.mut);
	philo->last_meal_time.val = time;
	pthread_mutex_unlock(&philo->last_meal_time.mut);
}

void	set_amount_eaten(t_philo *philo, uint_fast64_t amount)
{
	pthread_mutex_lock(&philo->amount_eaten.mut);
	philo->amount_eaten.val = amount;
	pthread_mutex_unlock(&philo->amount_eaten.mut);
}

void	set_alive_val(t_philo *philo, bool value)
{
	pthread_mutex_lock(&philo->alive.mut);
	philo->alive.val = value;
	pthread_mutex_unlock(&philo->alive.mut);
}

void	set_stop(t_philo *philo, bool stop)
{
	pthread_mutex_lock(&(philo->stop->mut));
	philo->stop->val = stop;
	pthread_mutex_unlock(&philo->stop->mut);
}
