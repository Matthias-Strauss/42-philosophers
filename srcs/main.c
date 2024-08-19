/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:34:42 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/18 11:51:09 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_params(int ac, char **av, t_philo *philo)
{
	philo->amount = str_to_int(av[1]); // replace atoi, LIBFT not authorized
	philo->time_to_die = str_to_int(av[2]);
	philo->time_to_eat = str_to_int(av[3]);
	philo->time_to_sleep = str_to_int(av[4]);
	if (av[5])
		philo->must_eat_amount = str_to_int(av[5]);
	else
		philo->must_eat_amount = 0;
}

void	start_watcher(t_program *prog)
{
}

void	init_philos(t_program *prog)
{
}

int	main(int ac, char **av)
{
	t_program		prog;
	t_philo			philo[MAX_THREADS];
	pthread_mutex_t	fork[MAX_THREADS];

	validate_args(ac, av);
	print_splash_screen();
	init_params(ac, av, &prog);
	init_philos(&prog);
	init_forks(&prog, &fork);
	// start_watcher(&prog);
	monitoring_loop(&prog);
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