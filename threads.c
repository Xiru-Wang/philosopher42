#include "philo.h"

//1. create philos threads
//2. crete monitor thread: check death || all full
//3. change flag in order to start simulation
//4. join

void	start_threads(t_data *data)
{
	int	i;

	i = -1;
	if (data->meals_must_have == 0)
		return ;
	else if (data->num_philos == 1)//only thread for lonely philo
		pthread_create(&data->philos[0].thread_id, NULL, die_lonely, &data->philos[0]);
	else
		while (++i < data->num_philos)//threads for > 1 philos
			pthread_create(&data->philos[i].thread_id, NULL, routine, &data->philos[i]);
	pthread_create(&data->thread_monitor, NULL, monitor, data);
	data->game_start_time = get_time();//now start the timestamp
	change_mutex(&data->data_mutex, &data->all_ready, YES);//change flag to run all threads
	//data->game_start = get_time();//before or after??
	i = -1;
	while (++i < data->num_philos)//all full??? what if someone dies
		pthread_join(data->philos[i].thread_id, NULL);//finished routine()
	change_mutex(&data->data_mutex, &data->game_over, YES);
	pthread_join(data->thread_monitor, NULL);
}

void	*die_lonely(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)//wait the flag to start the game
		if (check_mutex(&philo->data->data_mutex, &philo->data->all_ready) == YES)
			break ;
	philo->last_meal_time = get_time();
	pthread_mutex_lock(&philo->first_f->fork_mutex);
	print_msg(philo, TAKE_FORK);
	usleep(philo->data->time_to_die * 1000);
	pthread_mutex_unlock(&philo->first_f->fork_mutex);
	print_msg(philo, DIE);//?
	return (NULL);
}

void	*routine(void *ptr)//each philo will do it
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	while (1)
		if (check_mutex(&philo->data->data_mutex, &philo->data->all_ready) == YES)
			break ;
	philo->last_meal_time = get_time();
	if (philo->data->num_philos % 2 == 0)//eg 4 philos:1 && 3 eat first
	{
		if (philo->id % 2 == 0)
			usleep(1000);//maybe
	}
	else//5 philos: 2 && 4 eat first
	{
		if (philo->id % 2 == 1)
			thinking(philo);//or sleep??// or wait??
	}
	while (if_game_over(philo->data) == NO && if_one_full(philo) == NO)
	{
		//in the middle of eat || sleep || think, if full or die, it will stop
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	*monitor(void *ptr)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)ptr;
	while (if_game_over(data) == NO)
	{
		while (i < data->num_philos && if_game_over(data) == NO)
		{
			if (if_one_dies(&data->philos[i]) == YES)
			{
				change_mutex(&data->data_mutex, &data->game_over, YES);
				print_msg(&data->philos[i], DIE);
			}
			i++;
		}
	}
	return (NULL);
}