#include "philo.h"

static void	eating(t_philo *philo);
static void *die_lonely(void *ptr);
static void *routine(void *ptr);

int	start_threads(t_data *data)
{
	int	i;

	i = -1;
	if (data->meals_must_have == 0)
		return (ft_return("0 meals"));
	else if (data->num_philos == 1)
	{
		if (pthread_create(&data->philos[0].thread_id, NULL,
			die_lonely, &data->philos[0]))
			return (ft_return("pthread_create philo failed"));
	}
	else
	{
		while (++i < data->num_philos)
		{
			if (pthread_create(&data->philos[i].thread_id, NULL,
				routine, &data->philos[i]))
				return (ft_return("pthread_create philos failed"));
		}
	}
	if (pthread_create(&data->thread_monitor, NULL, monitor, data))
		return (ft_return("pthread_create monitor failed"));
	data->game_start_time = get_time();
	change_mutex(&data->all_ready_mutex, &data->all_ready, YES);
	i = -1;
	//calling thread will be blocked until philos threads complete its execution
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread_id, NULL);
	// if all philos join, means all full, so change game_over to YES
	change_mutex(&data->game_over_mutex, &data->game_over, YES);
	pthread_join(data->thread_monitor, NULL);
	return (SUCCESS);
}

static void	*die_lonely(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
		if (check_mutex(&philo->data->all_ready_mutex,
			&philo->data->all_ready) == YES)
			break ;
	philo->last_meal_time = get_time();
	pthread_mutex_lock(&philo->first_f->fork_mutex);
	print_msg(philo, TAKE_FORK);
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(&philo->first_f->fork_mutex);
	return (NULL);
}

static void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;

	while (1)
		if (check_mutex(&philo->data->all_ready_mutex,
			&philo->data->all_ready) == YES)
			break ;
	if (philo->id % 2 == 1)
		ft_usleep(100);
	while (if_game_over(philo->data) == NO)
	{
		eating(philo);
		print_msg(philo, SLEEP);
		if (check_mutex(&philo->is_full_mutex, &philo->is_full) == YES)
			return (NULL);//to ensure this philo finished its food
		ft_usleep(philo->data->time_to_sleep);
		print_msg(philo, THINK);
		//ft_usleep(0.2 * philo->data->time_to_eat);
	}
	return (NULL);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_f->fork_mutex);
	print_msg(philo, TAKE_FORK);
	if (if_game_over(philo->data) == YES)
		return ;// while waiting for the sec_fork, one phil could die
	pthread_mutex_lock(&philo->second_f->fork_mutex);
	print_msg(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->meal_time_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_time_mutex);
	print_msg(philo, EAT);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->first_f->fork_mutex);
	pthread_mutex_unlock(&philo->second_f->fork_mutex);
	philo->meals++;
	if (philo->meals == philo->data->meals_must_have)
		change_mutex(&philo->is_full_mutex, &philo->is_full, YES);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i].fork_mutex);
		pthread_mutex_destroy(&data->philos[i].is_full_mutex);
		pthread_mutex_destroy(&data->philos[i].meal_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->all_ready_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->game_over_mutex);
}
