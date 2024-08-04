/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:04:31 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/04 17:04:38 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_args(int ac, char **av)
{
	(void)av;
	validate_arg_count(ac);
	validate_positive_num(ac, av);
	return (1);
}

void	validate_arg_count(int count)
{
	if (!(count == 6 || count == 5))
	{
		printf("\n\033[31mOOPS! -- Something went wrong.\n\n\033[0m");
		printf("Please start philosophers with the following arguments:\n\n");
		printf("• number_of_philosophers\n");
		printf("• time_to_die (in ms)\n");
		printf("• time_to_eat\n");
		printf("• time_to_sleep\n\n");
		printf("• (OPTIONAL!) number_of_times_each_philosopher_must_eat\n\n");
		exit(1);
	}
}

void	validate_positive_num_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if ((*av[i] == '-'))
		{
			printf("NEGATIVE ARGUMENT DETECTED -- ABORT\n");
			exit(1);
		}
		i++;
	}
}
