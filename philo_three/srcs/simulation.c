/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:05 by user42            #+#    #+#             */
/*   Updated: 2020/12/10 03:06:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fork_and_eat(t_philo *philo)
{
	sem_wait(philo->env->picking);
	sem_wait(philo->env->forks);
	phil_fork(philo);
	sem_wait(philo->env->forks);
	sem_post(philo->env->picking);
	phil_fork(philo);
	phil_eat(philo);
	sem_post(philo->env->forks);
	sem_post(philo->env->forks);
}

void	*process_philosopher(void *param)
{
	t_philo	*philo;

	philo = (t_philo*)param;
	while (!is_finished(philo))
	{
		fork_and_eat(philo);
		if (!philo->set_fed_mutex &&
			get_mutexint(&philo->meals) >= philo->env->stngs.max_eat)
		{
			sem_post(philo->env->fed);
			philo->set_fed_mutex = 1;
		}
		phil_sleep(philo);
		phil_think(philo);
	}
	return (NULL);
}

int		starved(t_philo *philo)
{
	int ret;

	sem_wait(philo->last_eat.mutex);
	ret = get_time() - philo->last_eat.val >= philo->env->stngs.die_time;
	return (ret);
}

void	*wait_philosophers_death(void *param)
{
	t_philo	*philo;

	philo = (t_philo*)param;
	while (!is_finished(philo))
	{
		if (starved(philo))
		{
			if (!phil_die(philo))
			{
				sem_post(philo->last_eat.mutex);
				return (0);
			}
			sem_wait(philo->env->lock);
			sem_post(philo->last_eat.mutex);
			sem_post(philo->env->stop);
			return (0);
		}
		sem_post(philo->last_eat.mutex);
		phil_wait(1000);
	}
	return (NULL);
}

void	*wait_philosophers_fed(void *param)
{
	t_env	*env;
	int		i;

	env = (t_env*)param;
	i = 0;
	while (i < env->stngs.philo_nb)
	{
		sem_wait(env->fed);
		i++;
	}
	sem_post(env->stop);
	return (NULL);
}
