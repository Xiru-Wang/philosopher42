#include "philo.h"

//https://github.com/suspectedoceano/dining_philosophers/blob/main/init.c

static void	assign_forks(t_philo *philo, t_fork *forks);
static void init_philos(t_data *data);

int	init_data(t_data *data)
{
	int i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->forks = malloc(sizeof(t_fork) * data->num_philos);
	if (!data->philos || !data->forks)
		return (ft_return("Malloc Error"));
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i].fork_mutex, NULL);
		data->forks[i].fork_id = i;//do i need?
		i++;
	}
	data->all_ready = NO;
	data->game_over = NO;
	pthread_mutex_init(&data->data_mutex, NULL);
	init_philos(data);
	return (SUCCESS);
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
		//data->philos[i].data = data;??？？
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
