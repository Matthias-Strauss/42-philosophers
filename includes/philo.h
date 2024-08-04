/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 15:51:36 by mstrauss          #+#    #+#             */
/*   Updated: 2024/08/04 17:25:44 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

/* ---------------------- timeval struct for reference ---------------------- */
// struct	timeval
// {
// 	time_t tv_sec;       /* seconds since Jan. 1, 1970 */
// 	suseconds_t tv_usec; /* and microseconds */
// };

/* -------------------------------------------------------------------------- */
/*                                   STRUCTS                                  */
/* -------------------------------------------------------------------------- */

typedef struct s_philo
{
	unsigned int	amount;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	must_eat_amount;
}					t_philo;

/* -------------------------------------------------------------------------- */
/*                                  FUNCTIONS                                 */
/* -------------------------------------------------------------------------- */
int					main(int ac, char **av);
void				print_splash_screen(void);

/* --------------------------- Argument Validation -------------------------- */
int					validate_args(int ac, char **av);
void				validate_arg_count(int count);

#endif