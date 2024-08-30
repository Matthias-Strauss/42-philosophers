/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mut_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:52:15 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/30 14:22:02 by mstrauss         ###   ########.fr       */
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

bool	set_mut_struct_long(t_p_bool *pair, long value)
{
	pthread_mutex_lock(&pair->mut);
	pair->val = value;
	pthread_mutex_unlock(&pair->mut);
	return (true);
}
