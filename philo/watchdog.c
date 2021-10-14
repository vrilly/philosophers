#include "philosophers.h"

static int	check_philo(t_philosopher *data, struct timeval cur)
{
	int	d;

	d = ms_between_timestamps(&data->s_last_feeding, &cur);
	if (d > data->globals->args.time_to_die
		&& data->times_eaten != data->globals->args.times_to_eat)
	{
		pthread_mutex_lock(&data->globals->state_lock);
		data->globals->dead = data->philosopher_number;
		pthread_mutex_unlock(&data->globals->state_lock);
		printer(data, DIED, NULL);
		return (1);
	}
	return (0);
}

void	*watchdog(t_philosophers *philos)
{
	int				i;
	struct timeval	cur;

	while (philos->globals.dead == 0 && philos->globals.done != philos->globals.args.num_of_philosophers)
	{
		i = 0;
		gettimeofday(&cur, NULL);
		while (i < philos->globals.args.num_of_philosophers)
		{
			if (check_philo(philos->entities[i], cur))
				break ;
			i++;
		}		
		usleep(1000);
	}
	return (NULL);
}