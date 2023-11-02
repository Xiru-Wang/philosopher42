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

void	dinner_start(t_data *data, t_philo *philos)
{
	
	if (data->meals_must_eat == 0)
		return ;
	else if (data->num_philo == 1)
		die_lonely(philos);
	else
		thread_create(philos);
}


void	die_lonely(t_philo *philo)
{
	pthread_mutex_lock(philo->first_f);
	print_msg(philo, TAKE_FORK);
	usleep(philo->data->time_to_die);//starving to death
	pthread_mutex_unlock(philo->first_f);
	exit(1);
}


void	*routine(void *ptr)//bc pthread_create only accept void * type
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		usleep(1000);//so odd philo eat first
	if (philo->id == philo->data->num_philo && philo->id % 2)//eg. 1 and 5 will not race
		usleep(2000);//not sure
	while (philo->data->is_dead == NO)//todo, need mutex??
	{
		eat(philo);
		sleep(philo);
		think(philo);
	}
	return (ptr);
}

void	*monitor(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	while (1)
	{
		if (check_death(philos) == YES || reach_meals_must_eat(philos) == YES)
			break ;
	}
	return (ptr);
}