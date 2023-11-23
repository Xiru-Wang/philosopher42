/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiwang <xiwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:13:04 by xiwang            #+#    #+#             */
/*   Updated: 2023/11/23 20:37:20 by xiwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo);
static void	*die_lonely(void *ptr);
static void	*routine(void *ptr);

int	start_threads(t_data *data)
{
	int	i;

	i = -1;
	if (data->num_philos == 1)
	{
		if (pthread_create(&data->philos[0].thread_id, NULL,
				die_lonely, &data->philos[0]))
			return (ft_return("pthread_create philo failed"));
	}
	else
	{
		while (++i < data->num_philos)
			if (pthread_create(&data->philos[i].thread_id, NULL,
					routine, &data->philos[i]))
				return (ft_return("pthread_create philos failed"));
	}
	if (pthread_create(&data->thread_monitor, NULL, monitor, data))
		return (ft_return("pthread_create monitor failed"));
	change_mutex(&data->all_ready_mutex, &data->all_ready, YES);
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread_id, NULL);
	change_mutex(&data->game_over_mutex, &data->game_over, YES);
	pthread_join(data->thread_monitor, NULL);
	return (SUCCESS);
}

static void	*die_lonely(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (check_mutex(&philo->data->all_ready_mutex,
			&philo->data->all_ready) == NO)
		usleep(200);
	update_last_meal_time(philo);
	pthread_mutex_lock(&philo->first_f->fork_mutex);
	print_msg(philo, TAKE_FORK);
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(&philo->first_f->fork_mutex);
	return (NULL);
}

static void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (check_mutex(&philo->data->all_ready_mutex,
			&philo->data->all_ready) == NO)
		usleep(200);
	if (philo->id % 2 == 1)
		ft_usleep(1);
	while (if_game_over(philo->data) == NO)
	{
		eating(philo);
		print_msg(philo, SLEEP);
		if (check_mutex(&philo->is_full_mutex, &philo->is_full) == YES)
			return (NULL);
		if (if_game_over(philo->data) == NO)
			ft_usleep(philo->data->time_to_sleep);
		print_msg(philo, THINK);
		if (if_game_over(philo->data) == NO)//a smarter way?
			if (philo->data->time_to_think > 5)
				ft_usleep(philo->data->time_to_think * 0.8);
	}
	return (NULL);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_f->fork_mutex);
	print_msg(philo, TAKE_FORK);
	if (if_game_over(philo->data) == YES)
		return ;
	pthread_mutex_lock(&philo->second_f->fork_mutex);
	print_msg(philo, TAKE_FORK);
	update_last_meal_time(philo);
	print_msg(philo, EAT);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->first_f->fork_mutex);
	pthread_mutex_unlock(&philo->second_f->fork_mutex);
	philo->meals++;
	if (philo->meals == philo->data->meals_must_have)
		change_mutex(&philo->is_full_mutex, &philo->is_full, YES);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i].fork_mutex);
		pthread_mutex_destroy(&data->philos[i].is_full_mutex);
		pthread_mutex_destroy(&data->philos[i].meal_time_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->all_ready_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->game_over_mutex);
}
