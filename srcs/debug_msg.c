/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:26:05 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/30 20:52:03 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_err(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}

void	debug_msg(char *msg, t_philo *philo)
{
	if (DEBUG_FLAG == true)
	{
		pthread_mutex_lock(philo->speak_lck);
		print_err("DEBUG: ", 2);
		print_err("thread ", 2);
		print_err(int_to_str(philo->id), 2);
		print_err(": ", 2);
		print_err(msg, 2);
		print_err("\n", 2);
		pthread_mutex_unlock(philo->speak_lck);
	}
}
