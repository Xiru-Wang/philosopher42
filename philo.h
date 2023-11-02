/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiruwang <xiruwang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:05:10 by xiruwang          #+#    #+#             */
/*   Updated: 2023/11/02 14:37:52 by xiruwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>//gettimeofday
#include <pthread.h>
//1 sec = 1,000 milliseconds = 1,000,000 microseconds
# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define PHILO_MAX 200
# define NO 0
# define YES 1

typedef struct s_data
{
	int				num_philo;
	int				meals_must_eat;
	u_int64_t		time_to_die;
	u_int64_t		time_to_eat;
	u_int64_t		time_to_sleep;
	u_int64_t		game_start;
	int				is_dead;
	pthread_mutex_t	*is_dead_mutex;
	pthread_mutex_t	*print_mutex;
} t_data;

typedef struct s_philo
{
	int				id;
	int				count_meals;
	t_data			*data;
	u_int64_t		last_meal;
	pthread_t		thread;
	pthread_mutex_t *meals_mutex;
	pthread_mutex_t	*first_f;
	pthread_mutex_t	*second_f;
} t_philo;
