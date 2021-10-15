/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:23:48 by tjans             #+#    #+#             */
/*   Updated: 2021/10/15 14:38:14 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(t_philosopher *data)
{
	if (data->globals->args.num_of_philosophers == 1)
	{
		printer(data, THINKING, NULL);
		usleep_wrap((data->globals->args.time_to_die + 5) * 1000);
		return (NULL);
	}
	while (1)
	{
		p_eat(data);
		if (should_die(data))
			break ;
		if (check_if_done(data))
			return (NULL);
		printer(data, SLEEPING, NULL);
		usleep_wrap(data->globals->args.time_to_sleep * 1000);
		if (should_die(data))
			break ;
		printer(data, THINKING, NULL);
	}
	return (NULL);
}
