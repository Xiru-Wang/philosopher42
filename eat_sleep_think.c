#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_f->fork_mutex);
	print_msg(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->second_f->fork_mutex);
	print_msg(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->philo_mutex);
	print_msg(philo, EAT);
	philo->meals++;
	usleep(philo->data->time_to_eat * 1000);
	if (philo->meals == philo->data->meals_must_have)
		change_mutex(&philo->philo_mutex, &philo->is_full, YES);
	pthread_mutex_unlock(&philo->first_f->fork_mutex);
	pthread_mutex_unlock(&philo->second_f->fork_mutex);
}

void	sleeping(t_philo *philo)
{
	if (check_mutex(&philo->philo_mutex, &philo->is_full) == YES)
		return ;
	if (check_mutex(&philo->data->data_mutex, &philo->data->game_over) == YES)
		return ;
	print_msg(philo, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	if (check_mutex(&philo->philo_mutex, &philo->is_full) == YES)
		return ;
	if (check_mutex(&philo->data->data_mutex, &philo->data->game_over) == YES)
		return ;
	print_msg(philo, THINK);
	while (1)
	{
		//keep thinking until have both forks??
	}
}