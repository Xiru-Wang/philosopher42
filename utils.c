#include "philo.h"

void	handle_err(char *s)
{
	printf("%s\n", s);
	exit(1);
}

//1 millisecond (ms) = 0.001 second

//tv_sec: second
//tv_usec: micro PART
u_int64_t	get_time(void)
{
	struct timeval	tv;//struct to save time

	if (gettimeofday(&tv, NULL) == 0)//return 0：success
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);//convert to millisec
	else
		handle_error("gettimeofday failed\n");
}

void	print_msg(t_philo *philo, char *s)
{
	u_int64_t	time;

	pthread_mutex_lock(philo->data->print_mutex);
	time = get_time() - philo->data->game_start;
	if (check_death != YES)//&&(reach_meals_must_eat != YES)//too much work?
		printf("%llu %d %s\n", time, philo->id, s);
	pthread_mutex_unlock(philo->data->print_mutex);
}

int	check_death(t_philo *philo)//loop, monitor should do
{
	int	i;

	i = 0;
	while (i < philo->data->num_philo)
	{
		pthread_mutex_lock(philo->data->is_dead_mutex);
		if (get_time() - philo[i].last_meal >= philo->data->time_to_die)
		{
			philo->data->is_dead = YES;
			print_msg(&philo[i], DIE);
			return (YES);
		}
		pthread_mutex_unlock(philo->data->is_dead_mutex);
		i++;
	}
	return (NO);
}

//loop to check if everyone eat X amount meals, if yes, game over
int	reach_meals_must_eat(t_philo *philos)//loop, monitor should do
{
	int	i;
	int philo_finished_meals;

	i = 0;
	philo_finished_meals = 0;
	if (philo[i]->data->meals_must_eat == -1)
		return (NO);
	while (i < philos[0]->data->num_philo)
	{
		pthread_mutex_lock(philos[i]->meals_mutex);
		if (philos[i]->count_meals >= philos[0]->data->meals_must_eat)
			philo_finished_meals++;
		pthread_mutex_unlock(phils[i]->meals_mutex);
		i++;
	}
	if (philo_finished_meals == philos[0]->data->num_philo)
		return (YES);
	return (NO);
}


// void	*monitor(void *ptr)
// {
// 	t_philo	*philos;

// 	philos = (t_philo *)ptr;
// 	while (1)
// 	{
// 		if (check_death(philos) == YES || reach_meals_must_eat(philos) == YES)
// 			break ;
// 	}
// 	return (ptr);
// }

void	destroy_all(t_data *data, t_philo *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philo[i]->meals_mutex);
		i++;
	}
	pthread_mutex_destroy(data->is_dead_mutex);
	pthread_mutex_destroy(data->print_mutex);
}
