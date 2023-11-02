#include "philo.h"

# define FAIL -1
# define SUCCESS 2

int	create_philo_threads(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos->data->num_philo)
	{
		if (pthread_create(&(philos[i].thread), NULL, &routine, &(philos[i])) != 0)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	join_philo_threads(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos->data->num_philo)
	{
		if (pthread_join(philos->thread, NULL) != 0)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

void	thread_create(t_philo *philos)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, &monitor, philos) != 0)
		handle_error("monitor thread create failed");
	if (create_philo_threads(philos) == FAIL)
		handle_error("philos threads create failed");
	//destroy??
	if (join_philo_threads(philos) == FAIL)
		handle_error("philos threads join failed");
	//destroy?
}
