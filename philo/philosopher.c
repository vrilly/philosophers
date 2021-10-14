#include "philosophers.h"

static int	should_die(t_philosopher *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&data->globals->state_lock);
	if (data->globals->dead)
	{
		pthread_mutex_unlock(&data->globals->state_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->globals->state_lock);
	return (0);
}


static int	check_if_done(t_philosopher *data)
{
	data->times_eaten++;
	if (!data->globals->args.times_to_eat)
		return (0);
	if (data->times_eaten >= data->globals->args.times_to_eat)
		return (1);
	return (0);
}

static void	p_eat(t_philosopher *data)
{
	pthread_mutex_lock(data->cs_left->mutex);
	if (should_die(data))
	{
		pthread_mutex_unlock(data->cs_left->mutex);
		return ;
	}
	printer(data, TAKEN_FORK, NULL);
	pthread_mutex_lock(data->cs_right->mutex);
	if (should_die(data))
	{
		pthread_mutex_unlock(data->cs_left->mutex);
		pthread_mutex_unlock(data->cs_right->mutex);
		return ;
	}
	printer(data, TAKEN_FORK, NULL);
	printer(data, EATING, NULL);
	gettimeofday(&data->s_last_feeding, NULL);
	usleep_wrap(data->globals->args.time_to_eat * 1000);
	pthread_mutex_unlock(data->cs_left->mutex);
	pthread_mutex_unlock(data->cs_right->mutex);
}

void	*philosopher(t_philosopher *data)
{
	if (data->globals->args.num_of_philosophers == 1)
	{
		printer(data, THINKING, NULL);
		usleep_wrap(data->globals->args.time_to_die * 1000);
		printer(data, DIED, NULL);
		return (NULL);
	}
	while (1)
	{
		p_eat(data);
		if (should_die(data))
			break ;
		if (check_if_done(data))
			return (NULL);
		printer(data, SLEEPING, NULL);
		usleep_wrap(data->globals->args.time_to_sleep * 1000);
		if (should_die(data))
			break ;
		printer(data, THINKING, NULL);
	}
	return (NULL);
}
