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

	status = check_mutex(&data->game_over_mutex, &data->game_over);
	return (status);
}

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
}
