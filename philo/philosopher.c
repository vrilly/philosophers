#include "philosophers.h"

static int	get_timestamp(t_philosopher *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (ms_between_timestamps(data->start_time, &tv));
}

static int	p_eat(t_philosopher *data)
{
	struct timeval	tv;

	while (try_lock_cs(data))
	{
		usleep(5 * 1000 + (50 * data->philosopher_number));
		gettimeofday(&tv, NULL);
		if (data->args->time_to_die <
			ms_between_timestamps(&data->s_last_feeding, &tv))
			return (0);
	}
	printf("[%d] %d has taken a fork\n", get_timestamp(data),
		data->philosopher_number);
	printf("[%d] %d is eating\n", get_timestamp(data),
		data->philosopher_number);
	usleep(1000 * data->args->time_to_eat);
	gettimeofday(&data->s_last_feeding, NULL);
	unlock_cs(data);
	return (1);
}

void	*philosopher(t_philosopher *data)
{
	struct timeval	tv;

	while (1)
	{
		if (!p_eat(data))
			break ;
		printf("[%d] %d is sleeping\n", get_timestamp(data),
			data->philosopher_number);
		usleep(data->args->time_to_sleep * 1000);
		gettimeofday(&tv, NULL);
		if (data->args->time_to_die <
			ms_between_timestamps(&data->s_last_feeding, &tv))
			break ;
		printf("[%d] %d is thinking\n", get_timestamp(data),
			data->philosopher_number);
	}
	printf("[%d] %d died\n", get_timestamp(data),
		data->philosopher_number);
	return (NULL);
}
