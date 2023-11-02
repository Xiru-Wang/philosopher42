#include "philo.h"

int	main(int ac, char *av)
{
	t_data	data;//Stack allocation, automatic storage duration

	t_philo	philos[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (ac == 5 || ac == 6)
	{
		init_data(&data, av);
		init_philos(philos, &data);
		init_forks(forks, &data);
		dinner_start(&data, philos);//include thread_creat
		destroy_all(&data, philos, forks);
	}
	else
	{
		printf("Wrong input\n");
		printf("./philo 5 800 200 200 7(optional)\n");
		exit(1);
	}
}
