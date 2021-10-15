/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:24:24 by tjans             #+#    #+#             */
/*   Updated: 2021/10/15 13:03:54 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	print_usage(char *bin)
{
	printf("usage: %s %s %s %s\n", bin, "number_of_philosophers",
		"time_to_die time_to_eat time_to_sleep",
		"[number_of_times_each_philosopher_must_eat]");
	return (1);
}

static int	ret_error(t_philosophers *data)
{
	printf(
		"\n\nCRITICAL ERROR\nProgram aborted due to an runtime error in %s\n",
		data->crit_error);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philosophers	philosophers;

	memset(&philosophers, 0, sizeof(t_philosophers));
	if (get_args(&philosophers.globals.args, argc, argv))
		return (print_usage(*argv));
	philosophers.crit_error = "main";
	if (gettimeofday(&philosophers.globals.start_time, NULL)
		|| pthread_mutex_init(&philosophers.globals.state_lock, NULL)
		|| spawn_chopsticks(&philosophers)
		|| spawn_philosophers(&philosophers)
		|| pthread_join(philosophers.watchdog, NULL))
		return (ret_error(&philosophers));
	if (philosophers.globals.dead)
		printf("\nExecution stopped due to a death :(\n");
	else
		printf("\nExecution stopped after everyone ate enough\n%s\n",
			"May the philosophers live, be prosperous and be healthy!");
	cleanup(&philosophers);
	return (0);
}
