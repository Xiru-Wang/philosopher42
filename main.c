/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:12:06 by xiwang            #+#    #+#             */
/*   Updated: 2023/11/21 20:22:11 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//visualizer:
//https://nafuka11.github.io/philosophers-visualizer/

static void	print_meals(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->print_mutex);
	while (i < data->num_philos)
	{
		printf(G"%d had %d meals\n"RST, data->philos[i].id, 
			data->philos[i].meals);
		i++;
	}
	pthread_mutex_unlock(&data->print_mutex);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac == 5 || ac == 6)
	{
		data = (t_data *)malloc(sizeof(t_data));
		if (check_input(av) == ERROR)
			return (ft_return("check_input failed"));
		if (parse_input(data, av) == ERROR)
			return (ft_return("parse_input failed"));
		if (init_data(data) == ERROR)
			return (ft_return("init_data failed"));
		start_threads(data);
		print_meals(data);
		destroy_mutexes(data);
		free(data->philos);
		free(data->forks);
		free(data);
	}
	else
		printf("./philo 5 800 150 150 [8]\n");
	return (0);
}
