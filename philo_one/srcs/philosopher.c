/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:10 by user42            #+#    #+#             */
/*   Updated: 2020/12/08 21:20:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	phil_eat(t_philo *philo)
{
	int	t;

	t = get_time() - philo->env->start_time;
	if (get_mutexint(&philo->env->finish))
		return ;
	pthread_mutex_lock(&philo->last_eat.mutex);
	philo->last_eat.val = get_time();
	pthread_mutex_unlock(&philo->last_eat.mutex);
	pthread_mutex_lock(&philo->meals.mutex);
	philo->meals.val++;
	pthread_mutex_unlock(&philo->meals.mutex);
	log_philo(philo, t, " is eating.");
	phil_wait(philo->env->stngs.eat_time * 1000, philo->env);
}

void	phil_sleep(t_philo *philo)
{
	int	t;

	t = get_time() - philo->env->start_time;
	if (get_mutexint(&philo->env->finish))
		return ;
	log_philo(philo, t, " is sleeping.");
	phil_wait(philo->env->stngs.sleep_time * 1000, philo->env);
}

void	phil_die(t_philo *philo)
{
	int	t;

	t = get_time() - philo->env->start_time;
	if (get_mutexint(&philo->env->finish))
		return ;
	pthread_mutex_lock(&philo->env->finish.mutex);
	philo->env->finish.val = 1;
	pthread_mutex_unlock(&philo->env->finish.mutex);
	log_philo_force(philo, t, " died.");
}

void	phil_think(t_philo *philo)
{
	int	t;

	t = get_time() - philo->env->start_time;
	if (get_mutexint(&philo->env->finish))
		return ;
	log_philo(philo, t, " is thinking.");
	if (philo->env->stngs.philo_nb % 2)
		phil_wait((philo->env->stngs.eat_time
			- philo->env->stngs.sleep_time) * 999, philo->env);
	else if (philo->env->stngs.philo_nb % 2 &&
		(!(philo->id % 2) || philo->id == philo->env->stngs.philo_nb))
		phil_wait((philo->env->stngs.eat_time
			- philo->env->stngs.sleep_time) * 999, philo->env);
}

void	phil_fork(t_philo *philo)
{
	int	t;

	t = get_time() - philo->env->start_time;
	if (get_mutexint(&philo->env->finish))
		return ;
	log_philo(philo, t, " has taken a fork.");
}
