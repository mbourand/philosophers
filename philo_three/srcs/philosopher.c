/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:10 by user42            #+#    #+#             */
/*   Updated: 2020/11/13 13:33:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	phil_eat(t_philo *philo)
{
	int t;

	t = get_time() - philo->env->start_time;
	if (is_finished(philo))
		return ;
	sem_wait(philo->last_eat.mutex);
	philo->last_eat.val = get_time();
	sem_post(philo->last_eat.mutex);
	philo->meals.val++;
	sem_post(philo->ate);
	log_philo(philo, t, " is eating.");
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
	sem_post(philo->dead.mutex);
	log_philo_force(philo, t, " died.");
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
