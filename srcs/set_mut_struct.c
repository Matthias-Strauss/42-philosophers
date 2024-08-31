/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mut_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:52:15 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/30 22:35:52 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	set_mut_struct_bool(t_p_bool *pair, bool value)
{
	pthread_mutex_lock(&pair->mut);
	pair->val = value;
	pthread_mutex_unlock(&pair->mut);
	return (true);
}

uint64_t	set_mut_struct_uint64_t(t_p_uint64_t *pair, uint64_t value)
{
	pthread_mutex_lock(&pair->mut);
	pair->val = value;
	pthread_mutex_unlock(&pair->mut);
	return (true);
}
