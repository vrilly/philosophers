/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_chop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:24:22 by tjans             #+#    #+#             */
/*   Updated: 2021/10/15 14:38:44 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_chopstick_mutex(t_chopstick *chopstick)
{
	chopstick->owner = 0;
	chopstick->mutex = malloc(sizeof(pthread_mutex_t));
	if (!chopstick->mutex || pthread_mutex_init(chopstick->mutex, NULL))
		return (1);
	return (0);
}

int	spawn_chopsticks(t_philosophers *philosophers)
{
	int				i;
	t_chopstick		**ptr;

	philosophers->crit_error = "spawn_chopsticks";
	philosophers->chopsticks = malloc(sizeof(t_chopstick *)
			* philosophers->globals.args.num_of_philosophers);
	if (!philosophers->chopsticks)
		return (1);
	i = 0;
	while (i < philosophers->globals.args.num_of_philosophers)
	{
		ptr = philosophers->chopsticks + i;
		*ptr = malloc(sizeof(t_chopstick));
		if (!*ptr || init_chopstick_mutex(*ptr))
			return (1);
		i++;
	}
	return (0);
}
