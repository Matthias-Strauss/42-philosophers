/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:34:42 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/04 17:24:11 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_philo
{
	unsigned int	amount;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat_amount;
}					t_philo;

int	main(int ac, char **av)
{
	t_philo	philo;

	validate_args(ac, av);
	print_splash_screen();
	init_params(ac, av, &philo);
	return (0);
}

void	init_params(int ac, char **av, t_philo *philo)
{
	philo->amount = ft_atoi(av[1]); // replace atoi, LIBFT not authorized
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->must_eat_amount = ft_atoi(av[5]);
	else
		philo->must_eat_amount = 0;
}
