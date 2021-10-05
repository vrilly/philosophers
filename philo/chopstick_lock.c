#include "philosophers.h"

int	try_lock_cs(t_philosopher *data, t_chopstick *cs)
{
	pthread_mutex_lock(data->state_lock);
	if (cs->reserved)
	{
		pthread_mutex_unlock(data->state_lock);
		return (1);
	}
	cs->reserved = data->philosopher_number;
	pthread_mutex_unlock(data->state_lock);
	pthread_mutex_lock(cs->mutex);
	return (0);
}

void	unlock_cs(t_philosopher *data)
{
	pthread_mutex_lock(data->state_lock);
	data->cs_left->reserved = 0;
	data->cs_right->reserved = 0;
	pthread_mutex_unlock(data->cs_left->mutex);
	pthread_mutex_unlock(data->cs_right->mutex);
	pthread_mutex_unlock(data->state_lock);
}
