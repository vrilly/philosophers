#include "philosophers.h"

t_should_die	should_die(t_philosopher *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&data->globals->state_lock);
	if (data->globals->dead)
	{
		pthread_mutex_unlock(&data->globals->state_lock);
		return (BUDDY_DIED);
	}
	if (data->globals->args.time_to_die
		< ms_between_timestamps(&data->s_last_feeding, &tv))
	{
		data->globals->dead = 1;
		pthread_mutex_unlock(&data->globals->state_lock);
		return (STARVED);
	}
	pthread_mutex_unlock(&data->globals->state_lock);
	return (ALIVE);
}

int	should_die_wrap(t_philosopher *data, t_should_die *reason)
{
	*reason = should_die(data);
	if (*reason != ALIVE)
		return (1);
	return (0);
}
