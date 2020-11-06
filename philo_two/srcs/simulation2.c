/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:05 by user42            #+#    #+#             */
/*   Updated: 2020/11/06 02:06:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		starved(t_philo *philo)
{
	int ret;

	sem_wait(philo->last_eat.mutex);
	ret = get_time() - philo->last_eat.val >= philo->env->stngs.die_time;
	return (ret);
}

void	check_philo_death(t_env *env)
{
	int i;

	i = 0;
	while (i < env->stngs.philo_nb)
	{
		sem_wait(env->philos[i].meals.mutex);
		if (env->philos[i].meals.val < env->stngs.max_eat &&
			starved(env->philos + i))
		{
			sem_post(env->philos[i].meals.mutex);
			phil_die(env->philos + i);
			sem_post(env->philos[i].last_eat.mutex);
			return ;
		}
		else
		{
			sem_post(env->philos[i].meals.mutex);
			sem_post(env->philos[i].last_eat.mutex);
		}
		i++;
	}
}

void	wait_philosophers(t_env *env)
{
	sem_wait(env->finish.mutex);
	while (!env->finish.val)
	{
		sem_post(env->finish.mutex);
		check_philo_death(env);
		sem_wait(env->terminated.mutex);
		if (env->terminated.val == env->stngs.philo_nb)
		{
			sem_post(env->terminated.mutex);
			return ;
		}
		sem_post(env->terminated.mutex);
		sem_wait(env->finish.mutex);
	}
	sem_post(env->finish.mutex);
}

int		can_eat(t_philo *philo)
{
	(void)philo;
	return (1);
}
