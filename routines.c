#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (pthread_mutex_lock(philo->first_f) != 0)
		handle_error("lock fork failed");
	printf("%d %s\n", philo->id, TAKE_FORK);
	if (pthread_mutex_lock(philo->second_f) != 0)
		handle_error("lock fork failed");
	printf("%d %s\n", philo->id, TAKE_FORK);
}

void	drop_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->first_f) != 0);
		handle_error("unlock fork failed");
	if (pthread_mutex_unlock(philo->second_f) != 0)
		handle_error("unlock fork failed");
}

void	eating(t_philo *philo)
{
	if (philo->count_meals == philo->data->meals_must_eat)
		return (0);
	// if (philo->data->num_philo == 1)
	// {
	// 	pthread_mutex_lock(philo->first_f);
	// 	print_msg(philo, TAKE_FORK);
	// 	usleep(philo->data->time_to_die);//starving to death
	// 	pthread_mutex_unlock(philo->first_f);
	// 	return ;//?
	// }
	take_forks(philo);
	//int flag = 1;//?? do i need?
	print_msg(philo, EAT);
	philo->last_meal = get_time();
	philo->count_meals++;
	usleep(philo->data->time_to_eat * 1000);//convert to microseconds
	//int flag = 0;
	drop_forks(philo);
	return (1);
}

void	thinking(t_philo *philo)
{
	print_msg(philo, THINK);
	//think how long??
}

void	sleeping(t_philo *philo)
{
	print_msg(philo, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
}
