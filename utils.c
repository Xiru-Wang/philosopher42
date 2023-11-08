#include "philo.h"

int	ft_return(char *s)
{
	printf("%s\n", s);
	return (ERROR);
}

void	change_mutex(pthread_t *mutex, int *value, int status)
{
	pthread_mutex_lock(mutex);
	*value = status;//update value
	pthread_mutex_unlcok(mutex);
}

int	check_mutex(pthread_t *mutex, int *value)
{
	int	status;

	pthread_mutex_lock(mutex);
	status = *value;//get value
	pthread_mutex_unlcok(mutex);
	return (status);
}

int	if_game_over(t_data *data)
{
	int	status;

	status = check_mutex(&data->data_mutex, &data->game_over);
	return (status);
}

int	if_one_full(t_philo *philo)
{
	int	status;

	status = check_mutex(&philo->philo_mutex, &philo->is_full);
	return (status);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i].fork_mutex);
		pthread_mutex_destroy(&data->philos[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->data_mutex);
}


long	get_time(void)
{
	struct timeval	tv;//struct to save time

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000); // convert to millisec
}
