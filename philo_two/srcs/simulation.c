/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:05 by user42            #+#    #+#             */
/*   Updated: 2020/10/30 17:33:58 by user42           ###   ########.fr       */
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

int		try_eat(t_env *env, t_philo *philo)
{
	fork_and_eat(philo);
	if (philo->meals.val >= env->stngs.max_eat)
		return (1);
	phil_sleep(philo);
	phil_think(philo);
	return (0);
}

void	*process_philosopher(void *param)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo*)param;
	env = philo->env;
	sem_wait(env->finish.mutex);
	while (!env->finish.val)
	{
		sem_post(env->finish.mutex);
		if (try_eat(env, philo))
		{
			sem_wait(env->finish.mutex);
			break ;
		}
		sem_wait(env->finish.mutex);
	}
	sem_post(env->finish.mutex);
	sem_wait(env->terminated.mutex);
	env->terminated.val++;
	sem_post(env->terminated.mutex);
	return (NULL);
}
