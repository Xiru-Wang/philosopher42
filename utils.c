#include "philo.h"

int	ft_return(char *s)
{
	printf("%s\n", s);
	return (ERROR);
}

//full:skip message
//alive: print eat sleep think
//dead: print die
void	print_msg(t_philo *philo, char *s)
{
	long	time;

	if (check_mutex(&philo->philo_mutex, &philo->is_full) == YES)
		return ;
	pthread_mutex_lock(&philo->data->data_mutex);
	time = get_time() - philo->data->game_start_time;
	if (if_game_over(philo->data) != YES)//print eat sleep think
		printf("%ld %d %s\n", time, philo->id, s);
	else // if one died, print death
		printf("%ld %d %s\n", time, philo->id, s);
	pthread_mutex_unlock(&philo->data->data_mutex);
}

long	get_time(void)
{
	struct timeval	tv;//struct to save time

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000); // convert to millisec
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