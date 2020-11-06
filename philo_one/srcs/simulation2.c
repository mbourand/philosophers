/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:05 by user42            #+#    #+#             */
/*   Updated: 2020/11/05 20:57:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_fork(t_philo *philo, int index)
{
	while (philo->env->forks[index].last_philo.val == philo->id && philo->env
		->forks[index].uses - philo->meals.val < philo->env->stngs.max_eat
		&& is_finished(philo->env))
		;
}

int		starved(t_philo *philo)
{
	int ret;

	pthread_mutex_lock(&philo->last_eat.mutex);
	ret = get_time() - philo->last_eat.val >= philo->env->stngs.die_time;
	return (ret);
}

void	check_philo_death(t_env *env)
{
	int i;

	i = 0;
	while (i < env->stngs.philo_nb)
	{
		pthread_mutex_lock(&env->philos[i].meals.mutex);
		if (env->philos[i].meals.val < env->stngs.max_eat &&
			starved(env->philos + i))
		{
			pthread_mutex_unlock(&env->philos[i].meals.mutex);
			phil_die(env->philos + i);
			pthread_mutex_unlock(&env->philos[i].last_eat.mutex);
			return ;
		}
		else
		{
			pthread_mutex_unlock(&env->philos[i].meals.mutex);
			pthread_mutex_unlock(&env->philos[i].last_eat.mutex);
		}
		i++;
	}
}

void	wait_philosophers(t_env *env)
{
	pthread_mutex_lock(&env->finish.mutex);
	while (!env->finish.val)
	{
		pthread_mutex_unlock(&env->finish.mutex);
		check_philo_death(env);
		pthread_mutex_lock(&env->terminated.mutex);
		if (env->terminated.val == env->stngs.philo_nb)
		{
			pthread_mutex_unlock(&env->terminated.mutex);
			return ;
		}
		pthread_mutex_unlock(&env->terminated.mutex);
		pthread_mutex_lock(&env->finish.mutex);
	}
	pthread_mutex_unlock(&env->finish.mutex);
}

int		can_eat(t_philo *philo)
{
	int ret;
	int fst;
	int sec;

	ret = 1;
	fst = philo->id % 2 ? philo->l_fork : philo->r_fork;
	sec = (philo->id + 1) % 2 ? philo->l_fork : philo->r_fork;
	pthread_mutex_lock(&philo->env->forks[fst].last_philo.mutex);
	if (philo->env->forks[fst].last_philo.val == philo->id)
		ret = 0;
	pthread_mutex_unlock(&philo->env->forks[fst].last_philo.mutex);
	if (ret == 0)
		return (0);
	pthread_mutex_lock(&philo->env->forks[sec].last_philo.mutex);
	if (philo->env->forks[sec].last_philo.val == philo->id)
		ret = 0;
	pthread_mutex_unlock(&philo->env->forks[sec].last_philo.mutex);
	if (ret == 0)
		return (0);
	return (1);
}
