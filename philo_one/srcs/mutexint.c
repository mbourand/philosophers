/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 18:13:20 by user42            #+#    #+#             */
/*   Updated: 2020/12/03 14:35:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		get_mutexint(t_mutexint *mi)
{
	int cpy;

	pthread_mutex_lock(&mi->mutex);
	cpy = mi->val;
	pthread_mutex_unlock(&mi->mutex);
	return (cpy);
}

void	set_mutexint(t_mutexint *mi, int val)
{
	pthread_mutex_lock(&mi->mutex);
	mi->val = val;
	pthread_mutex_unlock(&mi->mutex);
}

void	inc_mutexint(t_mutexint *mi)
{
	pthread_mutex_lock(&mi->mutex);
	mi->val++;
	pthread_mutex_unlock(&mi->mutex);
}
