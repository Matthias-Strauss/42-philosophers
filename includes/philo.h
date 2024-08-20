/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:51:36 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/20 20:49:21 by mstrauss         ###   ########.fr       */
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

typedef struct s_p_uint
{
	unsigned int	val;
	pthread_mutex_t	mut;
}					t_p_uint;

typedef struct s_p_bool
{
	bool			val;
	pthread_mutex_t	mut;
}					t_p_bool;

typedef struct s_philo
{
	uint8_t			id;
	// bool			alive;
	t_p_uint		last_meal_time;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat_amount;
	t_p_bool		*l_fork;
	t_p_bool		*r_fork;
	t_p_uint		*speak_lck;
}					t_philo;

/// @brief speak_lck is also used as a death flag
typedef struct s_program
{
	uint8_t			amount;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat_amount;
	pthread_t		threads[MAX_THREADS];
	t_philo			philos[MAX_THREADS];
	t_p_bool		forks[MAX_THREADS];
	t_p_uint		speak_lck;
}					t_program;

/* -------------------------------------------------------------------------- */
/*                                  FUNCTIONS                                 */
/* -------------------------------------------------------------------------- */
int					main(int ac, char **av);
void				print_splash_screen(void);
int					get_time_ms(void);
void				better_sleep(size_t ms);
void				destroy_all_muts(t_program *prog);

/* --------------------------- Argument Validation -------------------------- */
int					validate_args(int ac, char **av);
void				validate_arg_count(int count);
void				validate_positive_num_args(int ac, char **av);
void				validate_arg_valid_chars(int ac, char **av);

/* ----------------------------- Initialization ----------------------------- */
void				init_prog(int ac, char **av, t_program *prog);

/* ------------------------------- Philosopher ------------------------------ */
void				*philo_routine(t_philo *philo, t_program *prog);

/* --------------------------------- Watcher -------------------------------- */

/* ---------------------------------- Utils --------------------------------- */
int					str_to_int(const char *str);
int					is_digit(int num);
int					is_space(int c);

#endif
