/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep_wrap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:24:39 by tjans             #+#    #+#             */
/*   Updated: 2021/10/15 13:05:21 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_wrap(unsigned int n)
{
	struct timeval	begin;
	struct timeval	temp;

	if (gettimeofday(&begin, NULL))
		return ;
	while (1)
	{
		usleep(100);
		if (gettimeofday(&temp, NULL))
			return ;
		if ((size_t)(((size_t)(temp.tv_sec - begin.tv_sec)) * 1000000 +
				((size_t)(temp.tv_usec - begin.tv_usec))) > n)
			break ;
	}
}
