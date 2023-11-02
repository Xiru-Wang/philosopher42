#include "philo.h"

unsigned int	atoi_unsigned(char *s)
{
	unsigned int	res;

	res = 0;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '-')
		handle_error("only positive values\n");
	if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	if (*s && (*s > '9' || *s < '0'))
		handle_error("only numbers\n");
	if (res == 0)
		handle_error("bigger than 0 please\n");
	return (res);
}

/*
 * ./philo
 * number_of_philosophers
 * time_to_die
 * time_to_eat
 * time_to_sleep
 * [number_of_times_each_philosopher_must_eat]
 * Check for max 200 philos
*/

void init_data(t_data *data, char *av)
{
	data->num_philo = atoi_unsigned(av[1]);
	if (data->num_philo > PHILO_MAX || data->num_philo < 1)
		handle_error("number of philos: 1 to 200\n");
	data->time_to_die = atoi_unsigned(av[2]);
	data->time_to_eat = atoi_unsigned(av[3]);
	data->time_to_sleep = atoi_unsigned(av[4]);
	if (av[5])
		data->meals_must_eat = atoi_unsigned(av[5]);
	else
		data->meals_must_eat = -1;
	data->game_start = get_time();
	data->is_dead = NO;
	pthread_mutex_init(data->is_dead_mutex, NULL);
	pthread_mutex_init(data->print_mutex, NULL);
}
