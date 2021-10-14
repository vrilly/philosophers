#include "philosophers.h"

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
	pthread_mutex_lock(data->cs_left->mutex);
	printer(data, TAKEN_FORK, NULL);
	pthread_mutex_lock(data->cs_right->mutex);
	printer(data, TAKEN_FORK, NULL);
	printer(data, EATING, NULL);
	gettimeofday(&data->s_last_feeding, NULL);
	usleep_wrap(data->args->time_to_eat * 1000);
	pthread_mutex_unlock(data->cs_left->mutex);
	pthread_mutex_unlock(data->cs_right->mutex);
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
		printer(data, SLEEPING, NULL);
		usleep_wrap(data->args->time_to_sleep * 1000);
		if (should_die_wrap(data, &die_reason))
			break ;
		printer(data, THINKING, NULL);
	}
	if (die_reason == STARVED)
		printer(data, DIED, NULL);
	return (NULL);
}
