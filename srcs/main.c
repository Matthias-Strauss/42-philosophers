/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:34:42 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/31 16:37:20 by mstrauss         ###   ########.fr       */
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
	prog->stop.val = false;
}

void	init_philos(t_program *prog)
{
	t_philo			*philos;
	uint64_t		start_time;
	unsigned int	i;

	i = 0;
	philos = prog->philos;
	start_time = get_time_ms() + (uint64_t)3000;
	while (i < prog->amount)
	{
		philos[i].id = i + 1;
		set_mut_struct_bool(&philos[i].alive, true);
		philos[i].start_time = start_time;
		philos[i].last_meal_time.val = philos[i].start_time;
		philos[i].time_to_die = prog->time_to_die;
		philos[i].time_to_eat = prog->time_to_eat;
		philos[i].time_to_sleep = prog->time_to_sleep;
		philos[i].must_eat_amount = prog->must_eat_amount;
		philos[i].l_fork = &prog->forks[i];
		philos[i].r_fork = &prog->forks[(i + 1) % prog->amount];
		philos[i].speak_lck = &prog->speak_lck;
		philos[i].stop = &prog->stop;
		i++;
	}
}

void	init_mutexs(t_program *prog)
{
	pthread_mutex_t	*forks;
	unsigned int	i;

	i = 0;
	forks = prog->forks;
	while (i < prog->amount)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			printf("ERROR while initializing Mutex.\n");
			exit(1);
		}
		if (pthread_mutex_init(&prog->philos[i].alive.mut, NULL) != 0)
		{
			printf("ERROR while initializing Mutex.\n");
			exit(1);
		}
		if (pthread_mutex_init(&prog->philos[i].last_meal_time.mut, NULL) != 0)
		{
			printf("ERROR while initializing Mutex.\n");
			exit(1);
		}
		i++;
	}
	if (pthread_mutex_init(&prog->speak_lck, NULL) != 0)
	{
		printf("ERROR while initializing Mutex.\n");
		exit(1);
	}
	if (pthread_mutex_init(&(prog->stop.mut), NULL) != 0)
	{
		printf("ERROR while initializing Mutex.\n");
		exit(1);
	}
}

void	launch_threads(t_program *prog)
{
	unsigned int	i;

	i = 0;
	if (prog->amount == 1)
	{
		if (pthread_create(&(prog->threads[i]), NULL, single_philo_routine,
				&(prog->philos[i])) != 0)
		{
			printf("Error while launching thread.\n");
			exit(2);
		}
	}
	else
	{
		while (i < prog->amount)
		{
			if (pthread_create(&(prog->threads[i]), NULL, philo_routine,
					&(prog->philos[i])) != 0)
			{
				printf("Error while launching thread.\n");
				exit(2);
			}
			i++;
		}
	}
}

// void	set_start_time(t_program *prog)
// {
// 	uint64_t	i;
// 	uint64_t	start_time;
// 	uint64_t	time_delta;
// 	t_philo		*philo;

// 	i = 0;
// 	philo = prog->philos;
// 	start_time = get_time_ms() + (uint64_t)1000;
// 	// printf("Current time: %" PRIu64 "\n", get_time_ms()); // DBG
// 	// printf("Start   time: %" PRIu64 "\n", start_time);    // DBG
// 	time_delta = (prog->time_to_die - (prog->time_to_eat
//				+ prog->time_to_sleep))
// 		/ prog->amount;
// 	// if (time_delta < 0) // DBG, actually not but check before submitting
// 	// 	time_delta = 1;
// 	while (i < prog->amount)
// 	{
// 		(philo[i]).start_time = start_time + (time_delta * i);
// 		set_mut_struct_uint64_t(&philo[i].last_meal_time,
// 			(philo[0]).start_time);
// 		// takes the time from the first philo
// 		i++;
// 	}
// }

int	main(int ac, char **av)
{
	t_program	prog;

	print_splash_screen();
	validate_args(ac, av);
	init_mutexs(&prog);
	init_prog(av, &prog);
	init_philos(&prog);
	// set_start_time(&prog);
	launch_threads(&prog);
	watcher(&prog);
	rejoin_threads(&prog);
	destroy_all_muts(&prog);
	return (0);
}

void	destroy_all_muts(t_program *prog)
{
	unsigned int	i;

	i = 0;
	while (i < prog->amount)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		pthread_mutex_destroy(&prog->philos[i].alive.mut);
		pthread_mutex_destroy(&prog->philos[i].last_meal_time.mut);
		i++;
	}
	pthread_mutex_destroy(&prog->speak_lck);
	pthread_mutex_destroy(&prog->stop.mut);
}

void	rejoin_threads(t_program *prog)
{
	unsigned int	i;

	i = 0;
	while (i < prog->amount)
	{
		pthread_join(prog->threads[i], NULL);
		i++;
	}
}

/*
pthread Functions

pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	void *(*start_routine) (void *), void *arg):
	Creates a new thread. The new thread starts execution by invoking start_routine with arg as its argument.

pthread_detach(pthread_t thread):
	Marks the thread identified by thread as detached. When a detached thread terminates,
		its resources are automatically released back to the system.

pthread_join(pthread_t thread, void **retval):
	Waits for the thread specified by thread to terminate. If retval is not NULL,
		the exit status of the thread is stored in the location pointed to by retval.

Mutex Functions
pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr):
	Initializes a mutex. Sets up the mutex pointed to by mutex according to the attributes specified in attr. If attr is NULL,
		the default mutex attributes are used.

pthread_mutex_destroy(pthread_mutex_t *mutex):
	Destroys the mutex object pointed to by mutex. The mutex must be unlocked and not currently referenced by any thread.

pthread_mutex_lock(pthread_mutex_t *mutex):
	Locks the mutex object pointed to by mutex. If the mutex is already locked,
	the calling thread blocks until the mutex becomes available.

pthread_mutex_unlock(pthread_mutex_t *mutex):
	Unlocks the mutex object pointed to by mutex. If there are threads blocked on the mutex when pthread_mutex_unlock() is called,
		one of them will become the new owner of the mutex.
*/