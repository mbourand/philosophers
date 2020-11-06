/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:05 by user42            #+#    #+#             */
/*   Updated: 2020/11/06 16:19:32 by user42           ###   ########.fr       */
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
	sem_wait(philo->dead.mutex);
	sem_wait(philo->meals.mutex);
	while (!philo->dead.val && philo->meals.val < philo->env->stngs.max_eat)
	{
		sem_post(philo->dead.mutex);
		if (philo->meals.val < philo->env->stngs.max_eat &&
			starved(philo))
		{
			phil_die(philo);
			sem_post(philo->meals.mutex);
			sem_post(philo->last_eat.mutex);
			exit(philo->exit_code);
			return (NULL);
		}
		sem_post(philo->meals.mutex);
		sem_post(philo->last_eat.mutex);
		phil_wait(10);
		sem_wait(philo->dead.mutex);
		sem_wait(philo->meals.mutex);
	}
	sem_post(philo->dead.mutex);
	return (NULL);
}

void	interpret_exit_code(t_env *env)
{
	int	status;
	int i;

	i = 0;
	if (waitpid(-1, &status, 0) <= 0)
		return ;
	if (WEXITSTATUS(status) == DEAD)
	{
		while (i < env->stngs.philo_nb)
			kill(env->philos[i++].thread, SIGKILL);
		env->terminated = env->stngs.philo_nb;
	}
	else if (WEXITSTATUS(status) == FED)
		env->terminated++;
}

void	wait_philosophers(t_env *env)
{
	while (env->terminated != env->stngs.philo_nb)
		interpret_exit_code(env);
}

int		can_eat(t_philo *philo)
{
	(void)philo;
	return (1);
}
