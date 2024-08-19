/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:04:31 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/18 18:46:37 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_args(int ac, char **av)
{
	(void)av;
	validate_arg_count(ac);
	validate_positive_num(ac, av);
	validate_arg_val_chars(ac, av);
	return (1);
}

/// @brief validates that mandatory arguments are given
/// @param count amount of strings in av
void	validate_arg_count(int ac)
{
	if (!(ac == 6 || ac == 5))
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

/// @brief validates that arguments are positive numbers
/// @param ac argc
/// @param av argv
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

/// @brief validates all program arguments to be integers
/// @param ac argc
/// @param av argv
void	validate_arg_val_chars(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i <= ac)
	{
		while (av[i][j])
		{
			if (!(is_digit(av[i][j])))
			{
				printf("\n\033[31mOOPS! -- Something went wrong.\
				\n\n\033[0m\nPlease start philosophers with the following \
				arguments:\n\n• number_of_philosophers\n• time_to_die (in ms)\
				\n• time_to_eat\n• time_to_sleep\n\n• (OPTIONAL!) \
				number_of_times_each_philosopher_must_eat\n\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

/// @brief checks if a character is a digit
/// @param num character to check
/// @return returns character if it IS a digit
/// 		returns 0 if character is NOT a digit
int	is_digit(int num)
{
	if (num >= '0' && num <= '9')
		return (num);
	return (0);
}
