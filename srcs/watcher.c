/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:18:24 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/19 17:58:42 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead_check(t_program *prog)
{
	uint8_t	i;
	t_philo	**tmp;
	uint8_t	amount;

	tmp = (t_philo **)prog->philos;
	while (1)
	{
		i = 0;
		while (i <= prog->amount)
		{
			if (!tmp[i]->alive)
			{
				// acquire death lock first ?
				prog->stop = true;
				break ;
			}
			i++;
		}
		if (!tmp[i]->alive)
			break ;
	}
}
