/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:17 by user42            #+#    #+#             */
/*   Updated: 2020/11/30 18:16:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	phil_wait(long micro)
{
	int time;
	int current;

	time = get_time();
	while (1)
	{
		usleep(1000);
		current = get_time();
		if (time + micro / 1000 <= current)
			break ;
	}
}
