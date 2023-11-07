#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>

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
	pthread_mutex_t fork_mutex;
	int fork_id;
}	t_fork;

typedef struct s_philo
{
	pthread_mutex_t philo_mutex;
	int	id;
	int	is_full;
	int	meals;
	pthread_t thread_id;
	u_int64_t last_meal_time;//to track if >= time_to_die;
	t_fork *first_f;
	t_fork *second_f;
	t_data *data;
} t_philo;

struct s_data
{
	int all_ready; // flag, if all_ready == YES, game start
	pthread_t thread_monitor;
	pthread_mutex_t data_mutex;
	int num_philos;
	u_int64_t time_to_die;
	u_int64_t time_to_eat;
	u_int64_t time_to_sleep;
	int meals_must_have;
	u_int64_t game_start;
	int game_over;//all full || one dies
	t_fork forks[PHILO_MAX];//t_fork *forks; cmallo || all forks[0,1,2,3,4]
	t_philo philos[PHILO_MAX];//all philos[0,1,2,3,4]
	//int is_full;
	//int is_dead;
	//int all_full;
};

//handle_input
int		check_input(char **av);
int		parse_input(t_data *data, char **av);
//utils
void	change_mutex(pthread_t *mutex, int *value, int status);
int		check_mutex(pthread_t *mutex, int *value);
int		if_game_over(t_data *data);
void	destroy_mutexes(t_data *data);
u_int64_t	get_time(void);
