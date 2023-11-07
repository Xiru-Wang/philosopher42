#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_f);
	print_msg(philo, TAKE_FORK);
	pthread_mutex_lock(philo->second_f);
	print_msg(philo, TAKE_FORK);
	philo->last_meal_time = get_time();
	print_msg(philo, EAT);
	philo->meals++;
	ft_sleep(philo->data->time_to_eat);
	if (philo->meals == philo->data->meals_must_have)
		change_mutex(&philo->philo_mutex, &philo->is_full, YES);
	pthread_mutex_unlock(philo->first_f);
	pthread_mutex_unlock(philo->second_f);
}