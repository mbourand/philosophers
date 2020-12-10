/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:05 by user42            #+#    #+#             */
/*   Updated: 2020/12/10 14:30:46 by user42           ###   ########.fr       */
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
	while (!get_mutexint(&philo->env->finish))
	{
		fork_and_eat(philo);
		if (!philo->set_fed_mutex && is_fed(philo))
		{
			inc_mutexint(&philo->env->fed);
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

int		wait_philosophers(t_env *env)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < env->stngs.philo_nb)
		{
			if (starved(env->philos + i))
			{
				phil_die(env->philos + i);
				sem_post(env->philos[i].last_eat.mutex);
				return (0);
			}
			else
				sem_post(env->philos[i].last_eat.mutex);
			i++;
		}
		if (get_mutexint(&env->fed) == env->stngs.philo_nb)
		{
			set_mutexint(&env->finish, 1);
			return (1);
		}
		phil_wait(1000, env);
	}
	return (0);
}
