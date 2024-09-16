/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:57:13 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/16 21:57:26 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	validate_lower_time_lim(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(is_digit(av[i][j])))
			{
				printf("\n\033[31mOOPS! -- Something went wrong.\
				\n\n\033[0m\nPlease start philosophers with the following \
				arguments:\n\n• number_of_philosophers\n• time_to_die (>60ms)\
				\n• time_to_eat (>60ms)\n• time_to_sleep (>60ms)\n\n• (OPTIONAL!) \
				number_of_times_each_philosopher_must_eat\n\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	validate_max_philos(char **av)
{
	if (str_to_int(av[1]) > MAX_THREADS)
	{
		printf("The maximum amount of philosophers is %d.\n", MAX_THREADS);
		printf("Please provide a number between 1 and %d.", MAX_THREADS);
		exit(1);
	}
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
		if (*av[i] == '-')
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
void	validate_arg_valid_chars(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
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
