#include "philosophers.h"

static void	p_eat(t_philosopher *data)
{
	pthread_mutex_lock(data->cs_left);
	printf("Philosopher %d took left fork\n", data->philosopher_number);
	pthread_mutex_lock(data->cs_right);
	printf("Philosopher %d took right fork\n", data->philosopher_number);
	printf("Philosopher %d is eating\n", data->philosopher_number);
	gettimeofday(&data->s_last_feeding, NULL);
	usleep(1000 * data->args->time_to_eat);
	printf("Philosopher %d finished eating\n", data->philosopher_number);
	pthread_mutex_unlock(data->cs_left);
	pthread_mutex_unlock(data->cs_right);
}

void	*philosopher(t_philosopher *data)
{
	struct timeval	s_cur;
	int				delta;

	printf("Philosopher %d spawned\n", data->philosopher_number);
	while (1)
	{
		p_eat(data);
		printf("Philosopher %d sleeps.\n", data->philosopher_number);
		usleep(data->args->time_to_sleep * 1000);
		gettimeofday(&s_cur, NULL);
		delta = ms_between_timestamps(&data->s_last_feeding, &s_cur);
		printf("Philosopher %d woke up! Took %dms\n", data->philosopher_number,
			delta);
		if (delta > data->args->time_to_die)
			break ;
	}
	printf("Philosopher %d died!\n", data->philosopher_number);
	return (NULL);
}
