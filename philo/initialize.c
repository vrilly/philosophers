#include "philosophers.h"

void	spawn_chopsticks(t_philosophers *philosophers)
{
	int				i;
	int				r;
	pthread_mutex_t	**ptr;

	philosophers->chopsticks = malloc(
			sizeof(pthread_mutex_t *) * philosophers->args.num_of_philosophers);
	i = 0;
	r = 0;
	while (i < philosophers->args.num_of_philosophers)
	{
		ptr = philosophers->chopsticks + i;
		*ptr = malloc(sizeof(pthread_mutex_t));
		r += pthread_mutex_init(*ptr, NULL);
		i++;
	}
}

static void	swap_chopsticks(t_philosopher *philo)
{
	pthread_mutex_t	*cs;

	cs = philo->cs_left;
	philo->cs_left = philo->cs_right;
	philo->cs_right = cs;
}

static void
	philo_setdata(t_philosopher *philo, t_philosophers *philosophers,
	int i, pthread_mutex_t **chopstick)
{
	philo->philosopher_number = i + 1;
	philo->args = &philosophers->args;
	philo->s_last_feeding = philosophers->start_time;
	philo->start_time = &philosophers->start_time;
	philo->cs_left = *chopstick;
	if (i < philosophers->args.num_of_philosophers - 1)
		philo->cs_right = *(chopstick + 1);
	else
		philo->cs_right = *philosophers->chopsticks;
	if (i % 2)
		swap_chopsticks(philo);
}

void	spawn_philosophers(t_philosophers *philosophers)
{
	int				i;
	t_philosopher	**ptr;
	pthread_mutex_t	**chopstick;

	philosophers->entities = malloc(
			sizeof(t_philosopher *) * philosophers->args.num_of_philosophers);
	i = 0;
	chopstick = philosophers->chopsticks;
	while (i < philosophers->args.num_of_philosophers)
	{
		ptr = philosophers->entities + i;
		*ptr = malloc(sizeof(t_philosopher));
		philo_setdata(*ptr, philosophers, i, chopstick);
		pthread_create(&(*ptr)->thread, NULL, (t_start_routine)philosopher,
			*ptr);
		i++;
		chopstick++;
	}
}
