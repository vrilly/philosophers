#include "philosophers.h"

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
	spawn_chopsticks(&philosophers);
	spawn_philosophers(&philosophers);
	pthread_join(philosophers.watchdog, NULL);
	if (philosophers.globals.dead)
		printf("\nExecution stopped due to a death :(\n");
	else
		printf("\nExecution stopped after everyone ate enough\n%s\n", 
				"May the philosophers live, be prosperous and be healthy!");
	cleanup(&philosophers);
	return (0);
}
