/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 20:47:55 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/16 20:50:51 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	get_voice(t_philo *philo)
{
	pthread_mutex_lock(&philo->speak_lck->mut);
}

inline uint_fast64_t	get_last_meal_time(t_philo *philo)
{
	uint_fast64_t	time;

	pthread_mutex_lock(&philo->last_meal_time.mut);
	time = philo->last_meal_time.val;
	pthread_mutex_unlock(&philo->last_meal_time.mut);
	return (time);
}

inline uint_fast64_t	get_amount_eaten(t_philo *philo)
{
	uint_fast64_t	amount;

	pthread_mutex_lock(&philo->amount_eaten.mut);
	amount = philo->amount_eaten.val;
	pthread_mutex_unlock(&philo->amount_eaten.mut);
	return (amount);
}

inline bool	get_alive_val(t_philo *philo)
{
	bool	alive;

	pthread_mutex_lock(&philo->alive.mut);
	alive = philo->alive.val;
	pthread_mutex_unlock(&philo->alive.mut);
	return (alive);
}

inline bool	carry_on(t_philo *philo)
{
	bool	value;

	pthread_mutex_lock(&philo->stop->mut);
	value = philo->stop->val;
	pthread_mutex_unlock(&philo->stop->mut);
	return (!value);
}
