/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_var.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:43:42 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/21 14:21:06 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// @brief Initializes a protected variable and its corresponding mutex.
/// @param var Struct containing the var and the mutex
/// @param state The initial bool value
void	init_p_bool(t_p_bool *var, bool state)
{
	var->val = state;
	pthread_mutex_init(&var->mut, NULL);
}

/// @brief Destroys a protected variable and its corresponding mutex.
/// @param var The protected variable struct
void	destroy_p_bool(t_p_bool *var)
{
	pthread_mutex_destroy(&var->mut);
}

/// @brief Initializes a protected variable and its corresponding mutex.
/// @param var Struct containing the var and the mutex
/// @param state The initial uint value
void	init_p_uint(t_p_uint *var, bool state)
{
	var->val = state;
	pthread_mutex_init(&var->mut, NULL);
}

/// @brief Destroys a protected variable and its corresponding mutex.
/// @param var The protected variable struct
void	destroy_p_uint(t_p_uint *var)
{
	pthread_mutex_destroy(&var->mut);
}
