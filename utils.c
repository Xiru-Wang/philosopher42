#include "philo.h"

int	ft_return(char *s)
{
	printf("%s\n", s);
	return (ERROR);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && (*s1 == *s2) && --n)
	// NOT n--, when n == 1, just return s1[0] - s2[0]
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	print_msg(t_philo *philo, char *s)
{
	long	time;

	// if (check_mutex(&philo->is_full_mutex, &philo->is_full) == YES)
	// 	return ;//delete, so once full, this philo will still print think and sleep
	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_time() - philo->data->game_start_time;
	if (if_game_over(philo->data) == NO)
	{
		if (ft_strncmp(EAT, s, 9) == 0)
			printf(B"%ld %d %s\n"RST, time, philo->id, s);
		else
			printf("%ld %d %s\n", time, philo->id, s);
	}
	else if (ft_strncmp(DIE, s, 5) == 0)
		printf(R"%ld %d %s\n"RST, time, philo->id, s);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

long	get_time(void)
{
	struct timeval	tv;//struct to save time

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000); // convert to millisec
}
