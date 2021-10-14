#include "philo.h"

static void	init_chopstick_mutex(t_chopstick *chopstick)
{
	chopstick->reserved = 0;
	chopstick->mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(chopstick->mutex, NULL);
}

void	spawn_chopsticks(t_philosophers *philosophers)
{
	int				i;
	t_chopstick		**ptr;

	philosophers->chopsticks = malloc(
			sizeof(t_chopstick *) * philosophers->globals.args.num_of_philosophers);
	i = 0;
	while (i < philosophers->globals.args.num_of_philosophers)
	{
		ptr = philosophers->chopsticks + i;
		*ptr = malloc(sizeof(t_chopstick));
		init_chopstick_mutex(*ptr);
		i++;
	}
}

static void	swap_chopsticks(t_philosopher *philo)
{
	t_chopstick	*cs;

	cs = philo->cs_left;
	philo->cs_left = philo->cs_right;
	philo->cs_right = cs;
}

static void
	philo_setdata(t_philosopher *philo, t_philosophers *philosophers,
	int i, t_chopstick **chopstick)
{
	philo->philosopher_number = i + 1;
	philo->times_eaten = 0;
	philo->globals = &philosophers->globals;
	philo->s_last_feeding = philosophers->globals.start_time;
	philo->cs_left = *chopstick;
	if (i < philosophers->globals.args.num_of_philosophers - 1)
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
	t_chopstick		**chopstick;

	philosophers->entities = malloc(sizeof(t_philosopher *)
			* philosophers->globals.args.num_of_philosophers);
	i = 0;
	chopstick = philosophers->chopsticks;
	while (i < philosophers->globals.args.num_of_philosophers)
	{
		ptr = philosophers->entities + i;
		*ptr = malloc(sizeof(t_philosopher));
		philo_setdata(*ptr, philosophers, i, chopstick);
		pthread_create(&(*ptr)->thread, NULL, (t_start_routine)philosopher,
			*ptr);
		pthread_detach((*ptr)->thread);
		i++;
		chopstick++;
	}
	usleep_wrap(1000);
	pthread_create(&philosophers->watchdog, NULL, (t_start_routine)watchdog, philosophers);
}
