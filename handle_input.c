#include "philo.h"

static int	all_num(char *s)
{
	int i;

	i = 0;
	if (s[0] == '0')
	{
		printf("bigger than 0 plz\n");
		return (ERROR);
	}
	while (s[i])
	{
		if (s[i] == '-' || s[i] < '0' || s[i] > '9')
		{
			printf("positive only && numbers only\n");
			return (ERROR);
		}
		i++;
	}
	if (i > 10)
	{
		printf("number is too big\n");
			return (ERROR);
	}
	return (SUCCESS);
}

int	check_input(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (all_num(av[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static long	atoi_long(char *s)
{
	long	res;

	res = 0;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s - '0');
		s++;
	}
	return (res);
}

int	parse_input(t_data *data, char **av)
{
	data->num_philos = atoi_long(av[1]);
	if (data->num_philos > PHILO_MAX || data->num_philos < 1)
	{
		printf("number of philos: 1 to 200\n");
		return (ERROR);
	}
	data->time_to_die = atoi_long(av[2]);
	data->time_to_eat = atoi_long(av[3]);
	data->time_to_sleep = atoi_long(av[4]);
	if (data->time_to_die < 60 ||data->time_to_eat < 60
		|| data->time_to_sleep < 60)//why??
	{
		printf("timestamp >= 60 milliseconds\n");
		return (ERROR);
	}
	if (av[5])
		data->meals_must_have = atoi_long(av[5]);
	else
		data->meals_must_have = -1;
	return (SUCCESS);
}
