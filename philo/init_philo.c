/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:40:23 by tjans             #+#    #+#             */
/*   Updated: 2021/10/15 12:59:00 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static int	philo_init(t_philosophers *philos, t_chopstick **c, int i)
{
	t_philosopher	**p;

	p = philos->entities + i;
	*p = malloc(sizeof(t_philosopher));
	if (!*p)
		return (1);
	philo_setdata(*p, philos, i, c);
	usleep_wrap(1000);
	if (pthread_create(&(*p)->thread, NULL, (t_start_routine)philosopher, *p)
		|| pthread_detach((*p)->thread))
		return (1);
	return (0);
}

int	spawn_philosophers(t_philosophers *philosophers)
{
	int				i;
	t_chopstick		**chopstick;

	philosophers->crit_error = "spawn_philosophers";
	philosophers->entities = malloc(sizeof(t_philosopher *)
			* philosophers->globals.args.num_of_philosophers);
	if (!philosophers->entities)
		return (1);
	i = 0;
	chopstick = philosophers->chopsticks;
	while (i < philosophers->globals.args.num_of_philosophers)
	{
		if (philo_init(philosophers, chopstick, i))
			return (1);
		i++;
		chopstick++;
	}
	usleep_wrap(1000);
	return (pthread_create(&philosophers->watchdog, NULL,
			(t_start_routine)watchdog, philosophers));
}
