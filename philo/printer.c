#include "philosophers.h"

static const char *msgs[] = {
	NULL,
	"has taken a fork",
	"is eating",
	"is sleeping",
	"is thinking",
	"died",
	"has eaten enough"
};

static int	get_timestamp(t_philosopher *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (ms_between_timestamps(&data->globals->start_time, &tv));
}

void	printer(t_philosopher *data, t_printer_msg msg, char *custom_msg)
{
	char	*p;

	pthread_mutex_lock(&data->globals->state_lock);
	if (msg == CUSTOM)
		p = custom_msg;
	else
		p = (char*)msgs[msg];
	if (!(data->globals->dead && msg != DIED))
	{
		if (msg == DONE)
			printf("[%d] %d %s, %d times!\n", get_timestamp(data),
					data->philosopher_number, p, data->times_eaten);
		else
			printf("[%d] %d %s\n", get_timestamp(data), data->philosopher_number, p);
	}
	pthread_mutex_unlock(&data->globals->state_lock);
}
