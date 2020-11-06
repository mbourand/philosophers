/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:01 by user42            #+#    #+#             */
/*   Updated: 2020/11/06 01:23:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		is_finished(t_env *env)
{
	int cpy;

	pthread_mutex_lock(&env->finish.mutex);
	cpy = env->finish.val;
	pthread_mutex_unlock(&env->finish.mutex);
	return (cpy);
}

int		get_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		exit(1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	phil_wait(long micro)
{
	struct timeval time;
	struct timeval current;

	gettimeofday(&time, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&current, NULL);
		if ((current.tv_sec - time.tv_sec) * 1000000 +
				(current.tv_usec - time.tv_usec) > micro)
			break ;
	}
}

void	log_philo(t_philo *philo, char *msg)
{
	int t;

	t = get_time() - philo->env->start_time;
	pthread_mutex_lock(&philo->env->log_mutex);
	pthread_mutex_lock(&philo->env->finish.mutex);
	if (philo->env->finish.val)
	{
		pthread_mutex_unlock(&philo->env->finish.mutex);
		pthread_mutex_unlock(&philo->env->log_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->env->finish.mutex);
	print_log(t, philo->id, msg);
	pthread_mutex_unlock(&philo->env->log_mutex);
}

void	log_philo_force(t_philo *philo, char *msg)
{
	int t;

	t = get_time() - philo->env->start_time;
	pthread_mutex_lock(&philo->env->log_mutex);
	print_log(t, philo->id, msg);
	pthread_mutex_unlock(&philo->env->log_mutex);
}
