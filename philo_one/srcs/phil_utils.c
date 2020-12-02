/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:01 by user42            #+#    #+#             */
/*   Updated: 2020/11/30 19:27:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_philo(t_philo *philo, int t, char *msg)
{
	if (get_mutexint(&philo->env->finish))
		return ;
	pthread_mutex_lock(&philo->env->log_mutex);
	print_log(t, philo->id, msg);
	pthread_mutex_unlock(&philo->env->log_mutex);
}

void	log_philo_force(t_philo *philo, int t, char *msg)
{
	pthread_mutex_lock(&philo->env->log_mutex);
	print_log(t, philo->id, msg);
	pthread_mutex_unlock(&philo->env->log_mutex);
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

int		is_fed(t_philo *philo)
{
	int ret;

	pthread_mutex_lock(&philo->meals.mutex);
	ret = philo->meals.val >= philo->env->stngs.max_eat;
	pthread_mutex_unlock(&philo->meals.mutex);
	return (ret);
}

void	free_env(t_env *env)
{
	int i;

	i = -1;
	while (++i < env->stngs.philo_nb)
	{
		pthread_mutex_destroy(&env->philos[i].meals.mutex);
		pthread_mutex_destroy(&env->philos[i].last_eat.mutex);
		pthread_mutex_destroy(&env->forks[i].mutex);
		pthread_mutex_destroy(&env->forks[i].last_philo.mutex);
	}
	pthread_mutex_destroy(&env->log_mutex);
	pthread_mutex_destroy(&env->finish.mutex);
	pthread_mutex_destroy(&env->fed.mutex);
	free(env->philos);
	free(env->forks);
}
