#include "philo.h"

void	change_mutex(pthread_mutex_t *lock, int *value, int status)
{
	pthread_mutex_lock(lock);
	*value = status;//update value
	pthread_mutex_unlock(lock);
}

int	check_mutex(pthread_mutex_t *lock, int *value)
{
	int	status;

	pthread_mutex_lock(lock);
	status = *value;//get value
	pthread_mutex_unlock(lock);
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

int	if_one_dies(t_philo *philo)
{
	int		status;
	long	time;

	pthread_mutex_lock(&philo->philo_mutex);
	time = get_time() - philo->last_meal_time;
	if (time >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->philo_mutex);
		status = YES;
		return (status);
	}
	pthread_mutex_lock(&philo->philo_mutex);
	return (NO);
}