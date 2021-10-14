#include "philosophers.h"

static void	join_threads(t_philosophers *philosophers)
{
	int				i;
	t_philosopher	*p;

	i = 0;
	while (i < philosophers->globals.args.num_of_philosophers)
	{
		p = *(philosophers->entities + i);
		pthread_join(p->thread, NULL);
		i++;
	}
}

static void	cleanup(t_philosophers *philo)
{
	int	i;

	i = 0;
	while (i < philo->globals.args.num_of_philosophers)
	{
		free((*(philo->chopsticks + i))->mutex);
		free(*(philo->chopsticks + i));
		free(*(philo->entities + i));
		i++;
	}
	free(philo->chopsticks);
	free(philo->entities);
}

int	main(int argc, char **argv)
{
	t_philosophers	philosophers;

	memset(&philosophers, 0, sizeof(t_philosophers));
	gettimeofday(&philosophers.globals.start_time, NULL);
	if (get_args(&philosophers.globals.args, argc, argv))
	{
		printf("usage: %s %s %s %s\n", *argv, "number_of_philosophers",
			"time_to_die time_to_eat time_to_sleep",
			"[number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	pthread_mutex_init(&philosophers.globals.state_lock, NULL);
	pthread_mutex_init(&philosophers.globals.print_lock, NULL);
	spawn_chopsticks(&philosophers);
	spawn_philosophers(&philosophers);
	join_threads(&philosophers);
	cleanup(&philosophers);
	return (0);
}
