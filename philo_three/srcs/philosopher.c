/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:10 by user42            #+#    #+#             */
/*   Updated: 2020/11/06 16:11:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	phil_eat(t_philo *philo)
{
	int t;

	t = get_time() - philo->env->start_time;
	if (is_finished(philo))
		return ;
	log_philo(philo, t, " is eating.");
	sem_wait(philo->meals.mutex);
	philo->meals.val++;
	sem_post(philo->meals.mutex);
	sem_wait(philo->last_eat.mutex);
	philo->last_eat.val = get_time();
	sem_post(philo->last_eat.mutex);
	phil_wait(philo->env->stngs.eat_time * 1000);
}

void	phil_sleep(t_philo *philo)
{
	int t;

	t = get_time() - philo->env->start_time;
	if (is_finished(philo))
		return ;
	log_philo(philo, t, " is sleeping.");
	phil_wait(philo->env->stngs.sleep_time * 1000);
}

void	phil_die(t_philo *philo)
{
	int t;

	t = get_time() - philo->env->start_time;
	sem_wait(philo->dead.mutex);
	philo->dead.val = 1;
	log_philo_force(philo, t, " died.");
	sem_post(philo->dead.mutex);
}

void	phil_think(t_philo *philo)
{
	int t;

	t = get_time() - philo->env->start_time;
	if (is_finished(philo))
		return ;
	log_philo(philo, t, " is thinking.");
}

void	phil_fork(t_philo *philo)
{
	int t;

	t = get_time() - philo->env->start_time;
	if (is_finished(philo))
		return ;
	log_philo(philo, t, " has taken a fork.");
}
