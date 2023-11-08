#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (check_input(av) == ERROR)
			return (ERROR);
		if (parse_input(&data, av) == ERROR)
			return (ERROR);
		if (init_data(&data) == ERROR)
			return (ERROR);
		start_threads(&data);
		destroy_mutexes(&data);
		free(data.philos);
		free(data.forks);
	}
	else
		printf("./philo 5 800 150 150 [8]\n");

	return (0);
}
