/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:05 by user42            #+#    #+#             */
/*   Updated: 2020/11/13 13:31:54 by user42           ###   ########.fr       */
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

void	*check_philo_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo*)arg;
	while (!is_finished(philo))
	{
		if (starved(philo))
		{
			phil_die(philo);
			sem_post(philo->last_eat.mutex);
			sem_post(philo->env->one_dead);
			return (NULL);
		}
		sem_post(philo->last_eat.mutex);
		phil_wait(2000);
	}
	return (NULL);
}

void	*wait_fed(void *param)
{
	t_env	*env;
	int		ttl;
	int		i;

	env = (t_env*)param;
	ttl = 0;
	while (ttl < env->stngs.max_eat)
	{
		i = 0;
		while (i < env->stngs.philo_nb)
			sem_wait(env->philos[i++].ate);
		ttl++;
	}
	sem_wait(env->log_mutex);
	write(1, "Everyone is fed.\n", 17);
	sem_post(env->one_dead);
	return (NULL);
}

void	wait_philosophers(t_env *env)
{
	int i;

	i = 0;
	sem_wait(env->one_dead);
	while (i < env->stngs.philo_nb)
		kill(env->philos[i++].thread, SIGKILL);
}
