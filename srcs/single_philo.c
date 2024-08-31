/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:25:23 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/30 23:33:13 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	get_l_fork(philo);
	better_sleep(philo->time_to_die);
	die(philo);
	return (1);
}
