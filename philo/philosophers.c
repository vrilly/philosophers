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

int	main(void)
{
	t_philosophers	philosophers;

	memset(&philosophers, 0, sizeof(t_philosophers));
	philosophers.cs_state = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philosophers.cs_state, NULL);
	gettimeofday(&philosophers.start_time, NULL);
	get_args(&philosophers.args, NULL);
	spawn_chopsticks(&philosophers);
	spawn_philosophers(&philosophers);
	join_threads(&philosophers);
}
