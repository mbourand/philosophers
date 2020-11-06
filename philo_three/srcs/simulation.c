/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:05 by user42            #+#    #+#             */
/*   Updated: 2020/11/06 15:48:15 by user42           ###   ########.fr       */
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
	if (can_eat(philo))
	{
		fork_and_eat(philo);
		if (philo->meals.val >= env->stngs.max_eat)
			return (1);
		phil_sleep(philo);
		phil_think(philo);
	}
	return (0);
}

void	*process_philosopher(void *param)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo*)param;
	env = philo->env;
	sem_wait(philo->dead.mutex);
	while (!philo->dead.val)
	{
		sem_post(philo->dead.mutex);
		if (try_eat(env, philo))
		{
			philo->exit_code = FED;
			break ;
		}
		sem_wait(philo->dead.mutex);
	}
	sem_post(philo->dead.mutex);
	return (NULL);
}
