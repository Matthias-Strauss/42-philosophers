/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:51:36 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/05 16:55:56 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef MAX_THREADS
#  define MAX_THREADS 200
# endif

# ifdef DEBUG
#  define DEBUG_FLAG true
# else
#  define DEBUG_FLAG false
# endif

# include <inttypes.h> // remove
# include <pthread.h>
# include <stdbool.h> // Add this line
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

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

typedef enum e_mutex_index
{
	LEFT_FORK = 0,
	RIGHT_FORK = 1,
	SPEAK_LOCK = 2,
	LAST_MEAL = 3,
	AMOUNT_EATEN = 4
}					t_mutex_index;
typedef struct s_p_uint64_t
{
	uint64_t		val;
	pthread_mutex_t	mut;
}					t_p_uint64_t;

typedef struct s_p_bool
{
	bool			val;
	pthread_mutex_t	mut;
}					t_p_bool;

typedef struct s_philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*speak_lck;
	t_p_uint64_t	last_meal_time;
	uint64_t		start_time;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		must_eat_amount;
	uint64_t		amount_eaten;
	uint64_t		id;
	uint8_t			locks_held;
	t_p_bool		alive;
	t_p_bool		*stop;
}					t_philo;

typedef struct s_program
{
	pthread_mutex_t	forks[MAX_THREADS];
	pthread_mutex_t	speak_lck;
	pthread_t		threads[MAX_THREADS];
	t_philo			philos[MAX_THREADS];
	uint64_t		amount;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		must_eat_amount;
	t_p_bool		stop;
}					t_program;
// typedef struct s_philo
// {
// 	unsigned int	id;
// 	t_p_bool		alive;
// 	t_p_uint		last_meal_time;
// 	unsigned int	time_to_die;
// 	unsigned int	time_to_eat;
// 	unsigned int	time_to_sleep;
// 	unsigned int	must_eat_amount;
// 	pthread_mutex_t	*l_fork;
// 	pthread_mutex_t	*r_fork;
// 	pthread_mutex_t	*speak_lck;
// }					t_philo;

// typedef struct s_program
// {
// 	unsigned int	amount;
// 	unsigned int	time_to_die;
// 	unsigned int	time_to_eat;
// 	unsigned int	time_to_sleep;
// 	int				must_eat_amount;
// 	pthread_t		threads[MAX_THREADS];
// 	t_philo			philos[MAX_THREADS];
// 	pthread_mutex_t	forks[MAX_THREADS];
// 	pthread_mutex_t	speak_lck;
// 	t_p_bool		stop;
// }					t_program;

/* -------------------------------------------------------------------------- */
/*                                  FUNCTIONS                                 */
/* -------------------------------------------------------------------------- */
int					main(int ac, char **av);
void				print_splash_screen(void);
uint64_t			get_time_ms(void);
void				better_sleep(uint64_t ms);
void				set_start_time(t_program *prog);
void				destroy_all_muts(t_program *prog);
bool				set_mut_struct_bool(t_p_bool *pair, bool value);
uint64_t			set_mut_struct_uint64_t(t_p_uint64_t *pair, uint64_t value);
void				debug_msg(char *msg, t_philo *philo);
char				*int_to_str(int n);
void				wait_to_start(uint64_t start_time);
void				destroy_all_muts(t_program *prog);
void				rejoin_threads(t_program *prog);

/* --------------------------- Argument Validation -------------------------- */
int					validate_args(int ac, char **av);
void				validate_arg_valid_chars(int ac, char **av);
void				validate_max_philos(char **av);
void				validate_arg_count(int count);
void				validate_positive_num_args(int ac, char **av);
void				validate_lower_time_lim(int ac, char **av);

/* ----------------------------- Initialization ----------------------------- */
void				init_prog(char **av, t_program *prog);
void				init_prog(char **av, t_program *prog);
void				init_philos(t_program *prog);
void				init_mutexs(t_program *prog);
void				launch_threads(t_program *prog);

/* ------------------------------- Philosopher ------------------------------ */
void				*philo_routine(void *arg);
void				*single_philo_routine(void *arg);

bool				p_acquire_utensils(t_philo *philo);
void				p_return_utensils(t_philo *philo);
void				p_eat(t_philo *philo);
void				p_sleep(t_philo *philo);
void				p_think(t_philo *philo);

bool				alive(t_philo *philo);
void				announce(t_philo *philo, /*uint64_t time,*/ char *msg);
void				die(t_philo *philo);

bool				get_fork(pthread_mutex_t *fork);
bool				get_l_fork(t_philo *philo);
bool				get_r_fork(t_philo *philo);

bool				return_fork(pthread_mutex_t *fork);
bool				return_l_fork(t_philo *philo);
bool				return_r_fork(t_philo *philo);

bool				get_voice(t_philo *philo);
bool				return_voice(t_philo *philo);

/* --------------------------------- Watcher -------------------------------- */
void				watcher(t_program *prog);
void				dead_check_loop(t_program *prog);
bool				check_vitals(t_philo *philo, t_program *prog);
bool				stop_flag_raised(t_p_bool *stop_flag);
void				kill_all(t_program *prog);
void				raise_stop_flag(t_p_bool *stop_flag);

/* ---------------------------------- Utils --------------------------------- */
int					str_to_int(const char *str);
int					is_digit(int num);
int					is_space(int c);

#endif
