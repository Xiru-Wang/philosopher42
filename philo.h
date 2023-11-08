#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
//#include <stdint.h>

# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

#define ERROR -1
#define SUCCESS 0
#define PHILO_MAX 200
#define YES 1
#define NO 2

typedef struct s_data t_data;//forward declaration

typedef struct s_forks
{
	pthread_mutex_t	fork_mutex;
	int				fork_id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				is_full;//share
	int				meals;
	long			last_meal_time;//share
	pthread_t		thread_id;
	t_fork			*first_f;
	t_fork			*second_f;
	t_data			*data;
	pthread_mutex_t	philo_mutex;
}	t_philo;

struct s_data
{
	int				num_philos;
	long			time_to_die;//u_int64_t not avaliable on linux??
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_must_have;
	int				all_ready; // flag, if all_ready == YES, game start
	long			game_start_time;
	int				game_over;//share, all full || one dies
	t_fork			*forks;
	t_philo			*philos;
	pthread_t		thread_monitor;
	pthread_mutex_t	data_mutex;
};

//handle_input
int		check_input(char **av);
int		parse_input(t_data *data, char **av);
//utils
int		ft_return(char *s);
void	change_mutex(pthread_t *mutex, int *value, int status);
int		check_mutex(pthread_t *mutex, int *value);
int		if_game_over(t_data *data);
int		if_one_full(t_philo *philo);
void	destroy_mutexes(t_data *data);
long	get_time(void);
