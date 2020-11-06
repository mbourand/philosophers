/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:10 by user42            #+#    #+#             */
/*   Updated: 2020/11/06 01:23:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	phil_eat(t_philo *philo)
{
	if (is_finished(philo->env))
		return ;
	log_philo(philo, " is eating.");
	pthread_mutex_lock(&philo->meals.mutex);
	philo->meals.val++;
	pthread_mutex_unlock(&philo->meals.mutex);
	pthread_mutex_lock(&philo->last_eat.mutex);
	philo->last_eat.val = get_time();
	pthread_mutex_unlock(&philo->last_eat.mutex);
	phil_wait(philo->env->stngs.eat_time * 1000);
}

void	phil_sleep(t_philo *philo)
{
	if (is_finished(philo->env))
		return ;
	log_philo(philo, " is sleeping.");
	phil_wait(philo->env->stngs.sleep_time * 1000);
}

void	phil_die(t_philo *philo)
{
	if (is_finished(philo->env))
		return ;
	pthread_mutex_lock(&philo->env->finish.mutex);
	philo->env->finish.val = 1;
	pthread_mutex_unlock(&philo->env->finish.mutex);
	log_philo_force(philo, " died.");
}

void	phil_think(t_philo *philo)
{
	if (is_finished(philo->env))
		return ;
	log_philo(philo, " is thinking.");
}

void	phil_fork(t_philo *philo)
{
	if (is_finished(philo->env))
		return ;
	log_philo(philo, " has taken a fork.");
}
