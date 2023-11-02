#include "philo.h"

void	dinner_start(t_data *data, t_philo *philo)
{
	int i;

	i = 0;
	if (data->meals_must_eat == 0)
		return ;
	else if (data->num_philo == 1)
		die_lonely(philo);
	else
	{
		while ( i < data->num_philo)
		{
			
		}
	}
}


void	die_lonely(t_philo *philo)
{
	pthread_mutex_lock(philo->first_f);
	print_msg(philo, TAKE_FORK);
	usleep(philo->data->time_to_die);//starving to death
	pthread_mutex_unlock(philo->first_f);
	return ;//?
}
