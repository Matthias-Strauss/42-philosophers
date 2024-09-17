/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:04:31 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/17 17:33:42 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_args(int ac, char **av)
{
	(void)av;
	if (validate_arg_count(ac) || validate_max_philos(av)
		|| validate_positive_num_args(ac, av) || validate_lower_time_lim(ac, av)
		|| validate_arg_valid_chars(ac, av))
		return (1);
	return (0);
}
