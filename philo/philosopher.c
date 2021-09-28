#include "philosophers.h"

static int	get_timestamp(t_philosopher *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (ms_between_timestamps(data->start_time, &tv));
}

static t_should_die	should_die(t_philosopher *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(data->state_lock);
	if (*data->dead)
	{
		pthread_mutex_unlock(data->state_lock);
		return (BUDDY_DIED);
	}
	if (data->args->time_to_die <
			ms_between_timestamps(&data->s_last_feeding, &tv))
	{
		*data->dead = 1;
		pthread_mutex_unlock(data->state_lock);
		return (STARVED);
	}
	pthread_mutex_unlock(data->state_lock);
	return (ALIVE);
}

static t_should_die	p_eat(t_philosopher *data)
{
	t_should_die die_reason;

	while (try_lock_cs(data))
	{
		usleep(5 * 1000 + (50 * data->philosopher_number));
		die_reason = should_die(data);
		if (die_reason)
			return (die_reason);
	}
	printf("[%d] %d has taken a fork\n", get_timestamp(data),
		data->philosopher_number);
	printf("[%d] %d is eating\n", get_timestamp(data),
		data->philosopher_number);
	usleep(1000 * data->args->time_to_eat);
	gettimeofday(&data->s_last_feeding, NULL);
	unlock_cs(data);
	return (0);
}

void	*philosopher(t_philosopher *data)
{
	t_should_die	die_reason;

	while (1)
	{
		die_reason = p_eat(data);
		if (die_reason || should_die(data))
			break ;
		printf("[%d] %d is sleeping\n", get_timestamp(data),
			data->philosopher_number);
		usleep(data->args->time_to_sleep * 1000);
		if (should_die(data))
			break ;
		printf("[%d] %d is thinking\n", get_timestamp(data),
			data->philosopher_number);
	}
	if (die_reason == STARVED)
		printf("[%d] %d died\n", get_timestamp(data),
			data->philosopher_number);
	return (NULL);
}
