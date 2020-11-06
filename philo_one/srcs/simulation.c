/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:05 by user42            #+#    #+#             */
/*   Updated: 2020/10/26 19:46:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	use_fork(t_philo *philo, int index)
{
	pthread_mutex_lock(&philo->env->forks[index].last_philo.mutex);
	philo->env->forks[index].last_philo.val = philo->id;
	pthread_mutex_unlock(&philo->env->forks[index].last_philo.mutex);
	philo->env->forks[index].uses++;
}

int		take_forks(t_philo *philo)
{
	int lr;
	int index;
	int ret;

	lr = 0;
	while (lr < 2)
	{
		index = (philo->id + lr) % 2 ? philo->l_fork : philo->r_fork;
		wait_fork(philo, index);
		if ((ret = is_finished(philo->env)))
			break ;
		pthread_mutex_lock(&philo->env->forks[index].mutex);
		phil_fork(philo);
		use_fork(philo, index);
		lr++;
	}
	if (lr == 2)
		return (ret);
	index = philo->id % 2 ? philo->l_fork : philo->r_fork;
	if (lr == 1)
		pthread_mutex_unlock(&philo->env->forks[index].mutex);
	return (ret);
}

void	fork_and_eat(t_philo *philo)
{
	int was_finished;

	was_finished = take_forks(philo);
	if (was_finished)
		return ;
	phil_eat(philo);
	pthread_mutex_unlock(&philo->env->forks[philo->l_fork].mutex);
	pthread_mutex_unlock(&philo->env->forks[philo->r_fork].mutex);
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
	pthread_mutex_lock(&env->finish.mutex);
	while (!env->finish.val)
	{
		pthread_mutex_unlock(&env->finish.mutex);
		if (try_eat(env, philo))
		{
			pthread_mutex_lock(&env->finish.mutex);
			break ;
		}
		pthread_mutex_lock(&env->finish.mutex);
	}
	pthread_mutex_unlock(&env->finish.mutex);
	pthread_mutex_lock(&env->terminated.mutex);
	env->terminated.val++;
	pthread_mutex_unlock(&env->terminated.mutex);
	return (NULL);
}
