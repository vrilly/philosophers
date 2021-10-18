/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:24:41 by tjans             #+#    #+#             */
/*   Updated: 2021/10/18 22:12:20 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo(t_philosopher *data, struct timeval cur)
{
	int	d;

	d = ms_between_timestamps(&data->s_last_feeding, &cur);
	if (d > data->globals->args.time_to_die
		&& data->times_eaten != data->globals->args.times_to_eat)
	{
		data->globals->dead = data->philosopher_number;
		if (pthread_mutex_unlock(&data->globals->state_lock))
			return ((int)prt_crt_err());
		printer(data, DIED, NULL);
		if (pthread_mutex_lock(&data->globals->state_lock))
			return ((int)prt_crt_err());
		return (1);
	}
	return (0);
}

static void	*prt_crt_err(void)
{
	printf("Critical error in watchdog!\n");
	return (NULL);
}

void	*watchdog(t_philosophers *philos)
{
	int				i;
	struct timeval	cur;

	while (1)
	{
		i = 0;
		if (pthread_mutex_lock(&philos->globals.state_lock)
			|| gettimeofday(&cur, NULL))
			return (prt_crt_err());
		while (i < philos->globals.args.num_of_philosophers)
		{
			if (check_philo(philos->entities[i], cur))
				break ;
			i++;
		}
		if (philos->globals.dead || philos->globals.done
			== philos->globals.args.num_of_philosophers)
			break ;
		if (pthread_mutex_unlock(&philos->globals.state_lock))
			return (prt_crt_err());
		usleep(1000);
	}
	if (pthread_mutex_unlock(&philos->globals.state_lock))
		prt_crt_err();
	return (NULL);
}
