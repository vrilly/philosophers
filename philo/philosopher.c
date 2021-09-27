#include "philosophers.h"

static int	get_timestamp(t_philosopher *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (ms_between_timestamps(data->start_time, &tv));
}

static void	p_eat(t_philosopher *data)
{
	pthread_mutex_lock(data->cs_left);
	printf("[%d] %d has taken a fork\n", get_timestamp(data),
		data->philosopher_number);
	pthread_mutex_lock(data->cs_right);
	printf("[%d] %d has taken a fork\n", get_timestamp(data),
		data->philosopher_number);
	printf("[%d] %d is eating\n", get_timestamp(data),
		data->philosopher_number);
	gettimeofday(&data->s_last_feeding, NULL);
	usleep(1000 * data->args->time_to_eat);
	pthread_mutex_unlock(data->cs_left);
	pthread_mutex_unlock(data->cs_right);
}

void	*philosopher(t_philosopher *data)
{
	while (1)
	{
		p_eat(data);
		printf("[%d] %d is sleeping\n", get_timestamp(data),
			data->philosopher_number);
		usleep(data->args->time_to_sleep * 1000);
		printf("[%d] %d is thinking\n", get_timestamp(data),
			data->philosopher_number);
	}
	printf("[%d] %d died\n", get_timestamp(data),
		data->philosopher_number);
	return (NULL);
}
