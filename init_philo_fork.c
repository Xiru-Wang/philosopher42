#include "philo.h"

void	init_forks(pthread_mutex_t *forks, t_data *data)
{
	int i;

	i = 0;
	while ( i < data->num_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
// to avoid deadlock
static void	assign_forks(t_philo *philo, pthread_mutex_t *forks)
{
	int id;

	id = philo->id;

	if (philo->id % 2 != 0)
	{
		philo->first_f = &forks[id];//left
		philo->second_f = &forks[id % philo->data->num_philo - 1];//right
	}
	else
	{
		philo->first_f = &forks[id % philo->data->num_philo - 1];//right
		philo->second_f = &forks[id];//left
	}
}

void	init_philo(t_philo *philos, pthread_mutex_t *forks)
{
	int		i;

	i = 0;//remember array always starts from 0
	while( i < philos->data->num_philo)
	{
		philos[i].id = i + 1;
		philos[i].count_meals = 0;
		pthread_mutex_init(philo[i]->meals_mutex, NULL);
		assign_forks(&philos[i], forks);//a pointer to a specific struct
		philos[i].last_meal = get_time();
		i++;
	}
}
