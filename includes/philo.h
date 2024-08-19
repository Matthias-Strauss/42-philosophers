/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:51:36 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/19 15:54:18 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# ifndef MAX_THREADS
#  define MAX_THREADS 200
# endif
# include <pthread.h>
# include <stdbool.h> // Add this line
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

/* ---------------------- timeval struct for reference ---------------------- */
// struct				timeval
// {
// 	time_t tv_sec;       /* seconds since Jan. 1, 1970 */
// 	suseconds_t tv_usec; /* and microseconds */
// };

// struct				timezone
// {
// 	int tz_minuteswest; /* of Greenwich */
// 	int tz_dsttime;     /* type of dst correction to apply */
// };

/* -------------------------------------------------------------------------- */
/*                                   STRUCTS                                  */
/* -------------------------------------------------------------------------- */

typedef struct s_philo
{
	uint8_t			id;
	bool			alive;
	unsigned int	last_meal_time;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat_amount;
	pthread_mutex_t	*l_fork_lck;
	pthread_mutex_t	*r_fork_lck;
	pthread_mutex_t	*spaghetti_lck;
	pthread_mutex_t	*speak_lck;
	pthread_mutex_t	*death_lck;
}					t_philo;	

typedef struct s_program
{
	uint8_t			amount;
	t_philo			philos[MAX_THREADS];
	pthread_mutex_t	forks[MAX_THREADS];
	pthread_mutex_t	spaghetti_lck;
	pthread_mutex_t	speak_lck;
	pthread_mutex_t	death_lck;
	bool			stop;
}					t_program;

/* -------------------------------------------------------------------------- */
/*                                  FUNCTIONS                                 */
/* -------------------------------------------------------------------------- */
int					main(int ac, char **av);
void				print_splash_screen(void);

/* --------------------------- Argument Validation -------------------------- */
int					validate_args(int ac, char **av);
void				validate_arg_count(int count);

#endif
