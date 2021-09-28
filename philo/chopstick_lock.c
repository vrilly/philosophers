#include "philosophers.h"

int	try_lock_cs(t_philosopher *data)
{
	int	avail;

	pthread_mutex_lock(data->cs_state);
	avail = 0;
	avail += data->cs_left->reserved;
	avail += data->cs_right->reserved;
	if (avail)
	{
		pthread_mutex_unlock(data->cs_state);
		return (1);
	}
	data->cs_left->reserved = 1;
	data->cs_right->reserved = 1;
	pthread_mutex_unlock(data->cs_state);
	pthread_mutex_lock(data->cs_left->mutex);
	pthread_mutex_lock(data->cs_right->mutex);
	return (0);
}

void	unlock_cs(t_philosopher *data)
{
	pthread_mutex_lock(data->cs_state);
	data->cs_left->reserved = 0;
	data->cs_right->reserved = 0;
	pthread_mutex_unlock(data->cs_left->mutex);
	pthread_mutex_unlock(data->cs_right->mutex);
	pthread_mutex_unlock(data->cs_state);
}