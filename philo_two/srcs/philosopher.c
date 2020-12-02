/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:10 by user42            #+#    #+#             */
/*   Updated: 2020/12/01 01:31:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	phil_eat(t_philo *philo)
{
	int	t;

	t = get_time() - philo->env->start_time;
	if (get_mutexint(&philo->env->finish))
		return ;
	set_mutexint(&philo->last_eat, get_time());
	inc_mutexint(&philo->meals);
	log_philo(philo, t, " is eating.");
	phil_wait(philo->env->stngs.eat_time * 1000);
}

void	phil_sleep(t_philo *philo)
{
	int	t;

	t = get_time() - philo->env->start_time;
	if (get_mutexint(&philo->env->finish))
		return ;
	log_philo(philo, t, " is sleeping.");
	phil_wait(philo->env->stngs.sleep_time * 1000);
}

void	phil_die(t_philo *philo)
{
	int	t;

	t = get_time() - philo->env->start_time;
	if (get_mutexint(&philo->env->finish))
		return ;
	set_mutexint(&philo->env->finish, 1);
	log_philo_force(philo, t, " died.");
}

void	phil_think(t_philo *philo)
{
	int	t;

	t = get_time() - philo->env->start_time;
	if (get_mutexint(&philo->env->finish))
		return ;
	log_philo(philo, t, " is thinking.");
}

void	phil_fork(t_philo *philo)
{
	int	t;

	t = get_time() - philo->env->start_time;
	if (get_mutexint(&philo->env->finish))
		return ;
	log_philo(philo, t, " has taken a fork.");
}
