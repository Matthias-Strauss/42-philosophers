/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:51:36 by mstrauss          #+#    #+#             */
/*   Updated: 2024/09/17 15:12:10 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef MAX_THREADS
#  define MAX_THREADS 200
# endif

# ifndef GROUP_OFFSET
#  define GROUP_OFFSET 0.8
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

typedef enum s_mutex_index
{
	LEFT_FORK = 0,
	RIGHT_FORK = 1,
	SPEAK_LOCK = 2,
	LAST_MEAL = 3,
	AMOUNT_EATEN = 4,
	ALIVE = 5,
	STOP = 6,
	WAITER = 7
}						t_mutex_index;
typedef struct s_p_uint_fast64_t
{
	uint_fast64_t		val;
	pthread_mutex_t		mut;
}						t_p_uint_fast64_t;

typedef struct s_p_uint_fast8_t
{
	uint_fast8_t		val;
	pthread_mutex_t		mut;
}						t_p_uint_fast8_t;

typedef struct s_p_bool
{
	bool				val;
	pthread_mutex_t		mut;
}						t_p_bool;

typedef struct s_waiter
{
	pthread_mutex_t		mut;
	bool				group;
	bool				skip;
	uint_fast8_t		count;
	uint_fast8_t		last_skipper;
	bool				someone_skipped;
}						t_waiter;

typedef struct s_philo
{
	t_p_bool			*l_fork;
	t_p_bool			*r_fork;
	t_p_uint_fast8_t	*speak_lck;
	t_p_uint_fast64_t	last_meal_time;
	t_p_uint_fast64_t	amount_eaten;
	t_p_bool			alive;
	uint_fast64_t		philo_count;
	uint_fast64_t		start_time;
	uint_fast64_t		time_to_die;
	uint_fast64_t		time_to_eat;
	uint_fast64_t		time_to_sleep;
	uint_fast64_t		must_eat_amount;
	uint_fast64_t		id;
	uint8_t				locks_held;
	t_p_bool			*stop;
}						t_philo;

typedef struct s_program
{
	t_p_bool			forks[MAX_THREADS];
	t_p_uint_fast8_t	speak_lck;
	t_p_bool			stop;
	pthread_t			threads[MAX_THREADS];
	t_philo				philos[MAX_THREADS];
	uint_fast64_t		amount;
	uint_fast64_t		time_to_die;
	uint_fast64_t		time_to_eat;
	uint_fast64_t		time_to_sleep;
	uint_fast64_t		must_eat_amount;
}						t_program;

/* -------------------------------------------------------------------------- */
/*                                  FUNCTIONS                                 */
/* -------------------------------------------------------------------------- */

/* ---------------------------------- Philo --------------------------------- */
void					*single_philo_routine(void *arg);
void					*philo_routine(void *arg);
void					init_time_offsets(t_philo *philo);
void					wait_to_start(uint_fast64_t start_time);
bool					think(t_philo *philo);
bool					announce(t_philo *philo, uint_fast64_t time, char *msg);
bool					stop(t_philo *philo);

bool					satiated(t_philo *philo);
uint_fast64_t			increase_amount_eaten(t_philo *philo);

bool					alive(t_philo *philo);
void					die(t_philo *philo);
uint_fast64_t			update_amount_eaten(t_philo *philo);

/* ---------------------------------- TIME ---------------------------------- */
uint_fast64_t			get_time_ms(void);
uint_fast64_t			get_run_time(t_philo *philo);
void					better_sleep(uint_fast64_t ms);

/* --------------------------- Getters and Setters -------------------------- */
uint_fast64_t			get_last_meal_time(t_philo *philo);
uint_fast64_t			get_amount_eaten(t_philo *philo);
void					get_voice(t_philo *philo);
bool					get_alive_val(t_philo *philo);
void					return_voice(t_philo *philo);
void					set_last_meal_time(t_philo *philo, uint_fast64_t time);
void					set_amount_eaten(t_philo *philo, uint_fast64_t amount);
void					set_alive_val(t_philo *philo, bool value);

void					set_stop(t_philo *philo, bool stop);
bool					carry_on(t_philo *philo);

/* ---------------------------------- Main ---------------------------------- */
int						main(int ac, char **av);
void					print_splash_screen(void);
void					set_start_time(t_program *prog);
void					rejoin_threads(t_program *prog);
void					destroy_all_muts(t_program *prog);

/* --------------------------- Argument Validation -------------------------- */
int						validate_args(int ac, char **av);
void					validate_arg_valid_chars(int ac, char **av);
void					validate_max_philos(char **av);
void					validate_arg_count(int count);
void					validate_positive_num_args(int ac, char **av);
void					validate_lower_time_lim(int ac, char **av);

/* ----------------------------- Initialization ----------------------------- */
void					init_mutexs(t_program *prog);
void					init_prog(char **av, t_program *prog);
void					init_philos(t_program *prog);
void					launch_threads(t_program *prog);

/* --------------------------------- Watcher -------------------------------- */
void					watcher(t_program *prog);
void					dead_check_loop(t_program *prog);
bool					check_starvation(t_philo *philo, t_program *prog);
bool					stop_flag_raised(t_p_bool *stop_flag);
void					kill_all(t_program *prog);
void					raise_stop_flag(t_p_bool *stop_flag);
void					watcher_announce(t_philo *philo, t_program *prog,
							char *msg);

/* ------------------------------- Char Utils ------------------------------- */
int						str_to_int(const char *str);
char					*int_to_str(int n);
int						is_digit(int num);
int						is_space(int c);

void					get_both_forks_odd(t_philo *philo);
void					get_both_forks_even(t_philo *philo);
void					return_both_forks_odd(t_philo *philo);
void					return_both_forks_even(t_philo *philo);

#endif
