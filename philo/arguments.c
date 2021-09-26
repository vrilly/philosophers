#include "philosophers.h"

void	get_args(t_args *args, char *input)
{
	(void)input;
	args->num_of_philosophers = 4;
	args->time_to_die = 600;
	args->time_to_eat = 200;
	args->time_to_sleep = 200;
}
