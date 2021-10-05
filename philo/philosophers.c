#include "philosophers.h"

static void	join_threads(t_philosophers *philosophers)
{
	int				i;
	t_philosopher	*p;

	i = 0;
	while (i < philosophers->args.num_of_philosophers)
	{
		p = *(philosophers->entities + i);
		pthread_join(p->thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philosophers	philosophers;

	memset(&philosophers, 0, sizeof(t_philosophers));
	philosophers.state_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philosophers.state_lock, NULL);
	gettimeofday(&philosophers.start_time, NULL);
	if (get_args(&philosophers.args, argc, argv))
	{
		printf("usage: %s %s %s %s\n", *argv, "number_of_philosophers",
			"time_to_die time_to_eat time_to_sleep",
			"[number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	spawn_chopsticks(&philosophers);
	spawn_philosophers(&philosophers);
	join_threads(&philosophers);
	return (0);
}
