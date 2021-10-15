/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:39:25 by tjans             #+#    #+#             */
/*   Updated: 2021/10/15 14:55:01 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_die(t_philosopher *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (pthread_mutex_lock(&data->globals->state_lock))
		return (-1);
	if (data->globals->dead)
	{
		if (pthread_mutex_unlock(&data->globals->state_lock))
			return (-1);
		return (1);
	}
	return (pthread_mutex_unlock(&data->globals->state_lock));
}

int	check_if_done(t_philosopher *data)
{
	data->times_eaten++;
	if (data->globals->args.times_to_eat == -1)
		return (0);
	if (data->times_eaten >= data->globals->args.times_to_eat)
	{
		printer(data, DONE, NULL);
		if (pthread_mutex_lock(&data->globals->state_lock))
			return (-1);
		data->globals->done++;
		if (pthread_mutex_unlock(&data->globals->state_lock))
			return (-1);
		return (1);
	}
	return (0);
}
