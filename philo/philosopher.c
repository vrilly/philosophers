#include "philosophers.h"

static int	get_timestamp(t_philosopher *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (ms_between_timestamps(data->start_time, &tv));
}

static int	check_if_done(t_philosopher *data)
{
	data->times_eaten++;
	if (!data->args->times_to_eat)
		return (0);
	if (data->times_eaten >= data->args->times_to_eat)
		return (1);
	return (0);
}

static t_should_die	p_eat(t_philosopher *data)
{
	t_should_die	die_reason;

	while (try_lock_cs(data, data->cs_left))
	{
		die_reason = should_die(data);
		if (die_reason)
			return (die_reason);
	}
	while (try_lock_cs(data, data->cs_right))
	{
		die_reason = should_die(data);
		if (die_reason)
			return (die_reason);
	}
	printf("[%d] %d has taken a fork\n", get_timestamp(data),
		data->philosopher_number);
	printf("[%d] %d is eating\n", get_timestamp(data),
		data->philosopher_number);
	gettimeofday(&data->s_last_feeding, NULL);
	usleep(1000 * data->args->time_to_eat);
	unlock_cs(data);
	return (0);
}

void	*philosopher(t_philosopher *data)
{
	t_should_die	die_reason;

	while (1)
	{
		die_reason = p_eat(data);
		if (die_reason || should_die_wrap(data, &die_reason))
			break ;
		if (check_if_done(data))
			return (NULL);
		printf("[%d] %d is sleeping\n", get_timestamp(data),
			data->philosopher_number);
		usleep(data->args->time_to_sleep * 1000);
		if (should_die_wrap(data, &die_reason))
			break ;
		printf("[%d] %d is thinking\n", get_timestamp(data),
			data->philosopher_number);
		delay(data);
	}
	if (die_reason == STARVED)
		printf("[%d] %d died\n", get_timestamp(data),
			data->philosopher_number);
	return (NULL);
}
