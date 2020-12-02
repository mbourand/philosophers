/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:01 by user42            #+#    #+#             */
/*   Updated: 2020/12/02 16:31:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_philo(t_philo *philo, int t, char *msg)
{
	if (get_mutexint(&philo->env->finish))
		return ;
	sem_wait(philo->env->log_mutex);
	print_log(t, philo->id, msg);
	sem_post(philo->env->log_mutex);
}

void	log_philo_force(t_philo *philo, int t, char *msg)
{
	sem_wait(philo->env->log_mutex);
	if (get_mutexint(&philo->env->finish))
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
		sem_close(env->philos[i].catch_stop);
		sem_close(env->philos[i].meals.mutex);
		sem_close(env->philos[i].last_eat.mutex);
		sem_unlink(env->philos[i].meals_name);
		sem_unlink(env->philos[i].lsteat_name);
		sem_unlink(env->philos[i].catch_name);
	}
	sem_close(env->log_mutex);
	sem_close(env->finish.mutex);
	sem_close(env->forks);
	sem_close(env->picking);
	sem_close(env->fed);
	sem_close(env->stop);
	sem_unlink("log");
	sem_unlink("finish");
	sem_unlink("forks");
	sem_unlink("picking");
	sem_unlink("fed");
	sem_unlink("stop");
	free(env->philos);
}
