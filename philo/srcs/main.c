/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:34:42 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/17 17:26:53 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_prog(char **av, t_program *prog)
{
	prog->amount = str_to_int(av[1]);
	prog->time_to_die = str_to_int(av[2]);
	prog->time_to_eat = str_to_int(av[3]);
	prog->time_to_sleep = str_to_int(av[4]);
	if (av[5])
		prog->must_eat_amount = str_to_int(av[5]);
	else
		prog->must_eat_amount = -1;
	pthread_mutex_lock(&prog->stop.mut);
	prog->stop.val = false;
	pthread_mutex_unlock(&prog->stop.mut);
}

void	init_philos(t_program *prog)
{
	t_philo			*philos;
	unsigned int	i;

	i = -1;
	philos = prog->philos;
	prog->start_time = UINT_FAST64_MAX;
	while (++i < prog->amount)
	{
		philos[i].id = i + 1;
		set_alive_val(&philos[i], true);
		philos[i].start_time = &prog->start_time;
		set_last_meal_time(&philos[i], *philos[i].start_time);
		set_amount_eaten(&philos[i], 0);
		philos[i].philo_count = prog->amount;
		philos[i].time_to_die = prog->time_to_die;
		philos[i].time_to_eat = prog->time_to_eat;
		philos[i].time_to_sleep = prog->time_to_sleep;
		philos[i].must_eat_amount = prog->must_eat_amount;
		philos[i].l_fork = &prog->forks[i];
		philos[i].r_fork = &prog->forks[(i + 1) % prog->amount];
		philos[i].speak_lck = &prog->speak_lck;
		philos[i].stop = &prog->stop;
		philos[i].start = &prog->start;
	}
}

void	init_mutexs(t_program *prog)
{
	t_p_bool		*forks;
	unsigned int	i;

	i = 0;
	forks = prog->forks;
	while (i < prog->amount)
	{
		if (pthread_mutex_init(&forks[i].mut, NULL) != 0
			|| pthread_mutex_init(&prog->philos[i].alive.mut, NULL) != 0
			|| pthread_mutex_init(&prog->philos[i].last_meal_time.mut,
				NULL) != 0
			|| pthread_mutex_init(&prog->philos[i].amount_eaten.mut, NULL) != 0)
		{
			printf("ERROR while initializing Mutex.\n");
			return ;
		}
		i++;
	}
	if (pthread_mutex_init(&prog->speak_lck.mut, NULL) != 0
		|| pthread_mutex_init(&prog->stop.mut, NULL) != 0
		|| pthread_mutex_init(&prog->start.mut, NULL) != 0)
		printf("ERROR while initializing Mutex.\n");
	return ;
}

void	launch_threads(t_program *prog)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&prog->start.mut);
	if (prog->amount == 1 && pthread_create(&(prog->threads[i]), NULL,
			single_philo_routine, &(prog->philos[i])) != 0)
	{
		printf("Error while launching thread.\n");
		return ;
	}
	if (prog->amount > 1)
	{
		while (i < prog->amount)
		{
			if (pthread_create(&(prog->threads[i]), NULL, philo_routine,
					&(prog->philos[i])) != 0)
			{
				printf("Error while launching thread.\n");
				return ;
			}
			i++;
		}
	}
	prog->start_time = get_time_ms();
	pthread_mutex_unlock(&prog->start.mut);
}

int	main(int ac, char **av)
{
	t_program	prog;

	print_splash_screen();
	validate_args(ac, av);
	prog.amount = str_to_int(av[1]);
	init_mutexs(&prog);
	init_prog(av, &prog);
	init_philos(&prog);
	launch_threads(&prog);
	watcher(&prog);
	rejoin_threads(&prog);
	destroy_all_muts(&prog);
	return (0);
}
