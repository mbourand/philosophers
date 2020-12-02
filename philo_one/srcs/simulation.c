/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:05 by user42            #+#    #+#             */
/*   Updated: 2020/11/30 19:27:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fork_and_eat(t_philo *philo)
{
	int lr;
	int index;

	lr = 0;
	while (lr < 2)
	{
		index = (philo->id + lr) % 2 ? philo->l_fork : philo->r_fork;
		pthread_mutex_lock(&philo->env->forks[index].mutex);
		phil_fork(philo);
		set_mutexint(&philo->env->forks[index].last_philo, philo->id);
		lr++;
	}
	phil_eat(philo);
	pthread_mutex_unlock(&philo->env->forks[philo->l_fork].mutex);
	pthread_mutex_unlock(&philo->env->forks[philo->r_fork].mutex);
}

void	*process_philosopher(void *param)
{
	t_philo	*philo;

	philo = (t_philo*)param;
	while (!get_mutexint(&philo->env->finish))
	{
		if (can_eat(philo))
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
	}
	return (NULL);
}

int		starved(t_philo *philo)
{
	int ret;

	pthread_mutex_lock(&philo->last_eat.mutex);
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
				pthread_mutex_unlock(&env->philos[i].last_eat.mutex);
				return (0);
			}
			else
				pthread_mutex_unlock(&env->philos[i].last_eat.mutex);
			i++;
		}
		if (get_mutexint(&env->fed) == env->stngs.philo_nb)
		{
			set_mutexint(&env->finish, 1);
			return (1);
		}
		phil_wait(1000);
	}
	return (0);
}

int		can_eat(t_philo *philo)
{
	int fst;
	int sec;

	fst = philo->id % 2 ? philo->l_fork : philo->r_fork;
	sec = (philo->id + 1) % 2 ? philo->l_fork : philo->r_fork;
	return (get_mutexint(&philo->env->forks[fst].last_philo) != philo->id
		&& get_mutexint(&philo->env->forks[sec].last_philo) != philo->id);
}
