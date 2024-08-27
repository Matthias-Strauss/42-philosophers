/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:34:42 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/27 15:33:58 by mstrauss         ###   ########.fr       */
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
}

void	init_philos(t_program *prog)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = prog->philos;
	while (i < prog->amount)
	{
		philos[i].id = i + 1;
		philos[i].alive.val = true;
		// add mutex locking before writing, also next line
		philos[i].last_meal_time.val = 0; // HOW TO FILL THIS?
		philos[i].time_to_die = prog->time_to_die;
		philos[i].time_to_eat = prog->time_to_eat;
		philos[i].time_to_sleep = prog->time_to_sleep;
		philos[i].must_eat_amount = prog->must_eat_amount;
		philos[i].l_fork = &prog->forks[i];
		philos[i].r_fork = &prog->forks[(i + 1) % prog->amount];
		philos[i].speak_lck = &prog->speak_lck;
		i++;
	}
}

void	init_mutexs(t_program *prog)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = prog->forks;
	while (i < prog->amount)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
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
}

void	launch_threads(t_program *prog)
{
	int	i;

	i = 0;
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

int	main(int ac, char **av)
{
	t_program	prog;

	print_splash_screen();
	validate_args(ac, av);
	init_prog(av, &prog);
	init_philos(&prog);
	launch_threads(&prog);
	watcher(&prog);
	// destroy_all_muts(&prog);
	// rejoin_threads();
	// destroy_mutexes();
	return (0);
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