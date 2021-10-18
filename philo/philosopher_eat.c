/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_eat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:59:56 by tjans             #+#    #+#             */
/*   Updated: 2021/10/18 22:05:48 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_chop(t_philosopher *data, t_chopstick *chopstick)
{
	if (pthread_mutex_lock(chopstick->mutex))
		return (1);
	chopstick->owner = data->philosopher_number;
	printer(data, TAKEN_FORK, NULL);
	return (0);
}

static int	eat_and_release_chop(t_philosopher *data)
{
	int	fail;

	fail = 0;
	printer(data, EATING, NULL);
	if (pthread_mutex_lock(&data->globals->state_lock))
		return (1);
	if (gettimeofday(&data->s_last_feeding, NULL))
		fail++;
	if (pthread_mutex_unlock(&data->globals->state_lock))
		fail++;
	usleep_wrap(data->globals->args.time_to_eat * 1000);
	data->cs_left->owner = 0;
	data->cs_right->owner = 0;
	if (pthread_mutex_unlock(data->cs_left->mutex)
		|| pthread_mutex_unlock(data->cs_right->mutex))
		fail++;
	return (fail);
}

int	p_eat(t_philosopher *data)
{
	if (lock_chop(data, data->cs_left))
		return (-1);
	if (should_die(data))
		return (1);
	if (lock_chop(data, data->cs_right))
		return (-1);
	if (should_die(data))
		return (1);
	return (eat_and_release_chop(data));
}
