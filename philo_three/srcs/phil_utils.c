/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:01 by user42            #+#    #+#             */
/*   Updated: 2020/12/10 03:10:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		is_finished(t_philo *philo)
{
	sem_wait(philo->env->lock);
	sem_post(philo->env->lock);
	return (get_mutexint(&philo->env->finish));
}

void	log_philo(t_philo *philo, int t, char *msg)
{
	if (is_finished(philo))
		return ;
	sem_wait(philo->env->log_mutex);
	print_log(t, philo->id, msg);
	sem_post(philo->env->log_mutex);
}

void	log_philo_force(t_philo *philo, int t, char *msg)
{
	sem_wait(philo->env->log_mutex);
	if (is_finished(philo))
	{
		sem_post(philo->env->log_mutex);
		return ;
	}
	print_log(t, philo->id, msg);
}

void	print_log(int t, int id, char *msg)
{
	static char	buf[256];
	int			i;

	ft_itoa(t, buf);
	i = ft_numlen(t);
	buf[i++] = ' ';
	ft_itoa(id, buf + i);
	i += ft_numlen(id);
	ft_strcpy(buf + i, msg);
	i += ft_strlen(msg);
	buf[i++] = '\n';
	write(1, buf, i);
	while (--i >= 0)
		buf[i] = 0;
}

void	free_env(t_env *env)
{
	int i;

	i = -1;
	while (++i < env->stngs.philo_nb)
	{
		free_sem(env->philos[i].catch_stop, env->philos[i].catch_name);
		free_sem(env->philos[i].meals.mutex, env->philos[i].meals_name);
		free_sem(env->philos[i].last_eat.mutex, env->philos[i].lsteat_name);
	}
	free_sem(env->log_mutex, "log");
	free_sem(env->finish.mutex, "finish");
	free_sem(env->forks, "forks");
	free_sem(env->picking, "picking");
	free_sem(env->fed, "fed");
	free_sem(env->stop, "stop");
	free_sem(env->lock, "lock");
	free(env->philos);
}
