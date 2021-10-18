/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:23:48 by tjans             #+#    #+#             */
/*   Updated: 2021/10/18 22:12:56 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_loop(t_philosopher *data)
{
	int	ret;

	while (1)
	{
		ret = p_eat(data);
		if (ret)
			break ;
		ret = should_die(data);
		if (ret)
			break ;
		if (check_if_done(data))
			break ;
		printer(data, SLEEPING, NULL);
		usleep_wrap(data->globals->args.time_to_sleep * 1000);
		ret = should_die(data);
		if (ret)
			break ;
		printer(data, THINKING, NULL);
	}
	if (ret == -1)
		printf("Critical error happened in philo %d.\n",
			data->philosopher_number);
}

void	*philosopher(t_philosopher *data)
{
	if (data->globals->args.num_of_philosophers == 1)
	{
		printer(data, THINKING, NULL);
		usleep_wrap((data->globals->args.time_to_die + 5) * 1000);
		return (NULL);
	}
	philo_loop(data);
	return (NULL);
}
