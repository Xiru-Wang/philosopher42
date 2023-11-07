#include "philo.h"

static void assign_forks(t_philo *philo, t_fork *forks);
static void init_philos(t_data *data);

void	init_data(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i].fork_mutex, NULL);
		data->forks[i].fork_id = i;
		i++;
	}
	//data->is_dead = NO;
	//data->all_full = NO;
	//data->game_start = get_time();
	data->all_ready = NO;
	data->game_over = NO;
	pthread_mutex_init(&data->data_mutex, NULL);
	init_philos(data);
}

static void	init_philos(t_data *data)
{
	int		i;

	i = 0;
	while( i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].is_full = NO;
		data->philos[i].last_meal_time = get_time();
		pthread_mutex_init(&data->philos[i].philo_mutex, NULL);
		assign_forks(&data->philos[i], data->forks);
		i++;
	}
}

static void	assign_forks(t_philo *philo, t_fork *forks)
{
	int i;

	i = philo->id;

	if (philo->id % 2 != 0)
	{
		philo->first_f = &forks[i];//left forks[1]
		philo->second_f = &forks[i % philo->data->num_philos - 1];//right forks[0]
	}
	else
	{
		philo->first_f = &forks[i % philo->data->num_philos - 1];//right
		philo->second_f = &forks[i];//left
	}
}
