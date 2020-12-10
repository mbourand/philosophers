/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 18:13:20 by user42            #+#    #+#             */
/*   Updated: 2020/12/10 03:41:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		get_mutexint(t_mutexint *mi)
{
	int cpy;

	sem_wait(mi->mutex);
	cpy = mi->val;
	sem_post(mi->mutex);
	return (cpy);
}

void	set_mutexint(t_mutexint *mi, int val)
{
	sem_wait(mi->mutex);
	mi->val = val;
	sem_post(mi->mutex);
}

void	inc_mutexint(t_mutexint *mi)
{
	sem_wait(mi->mutex);
	mi->val++;
	sem_post(mi->mutex);
}

void	free_sem(sem_t *mutex, char *name)
{
	sem_unlink(name);
	sem_close(mutex);
}
