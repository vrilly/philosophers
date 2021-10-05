#include "philosophers.h"

void	delay(t_philosopher *data)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	if (ms_between_timestamps(&data->s_last_feeding, &cur)
		+ data->args->time_to_sleep / 2
		< data->args->time_to_die)
		if (data->args->num_of_philosophers % 2)
			usleep(10000);
	if (data->times_eaten > 1)
		return ;
	if (data->philosopher_number % 2)
		usleep(100);
}
