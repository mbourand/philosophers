/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:17 by user42            #+#    #+#             */
/*   Updated: 2020/10/28 01:27:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int i)
{
	unsigned int	nb;

	nb = (i < 0 ? -i : i);
	if (nb >= 10)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
}

int		ft_atoui(const char *s)
{
	int res;
	int i;

	i = -1;
	res = 0;
	if (!s || !s[0])
		return (-1);
	while (s[++i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		res = res * 10 + (s[i] - '0');
	}
	return (res);
}

void	free_env(t_env *env)
{
	int i;

	i = -1;
	while (++i < env->stngs.philo_nb)
	{
		sem_close(env->philos[i].meals.mutex);
		sem_close(env->philos[i].last_eat.mutex);
		sem_unlink(env->philos[i].meals_name);
		sem_unlink(env->philos[i].lsteat_name);
		free(env->philos[i].lsteat_name);
		free(env->philos[i].meals_name);
	}
	sem_close(env->log_mutex);
	sem_close(env->terminated.mutex);
	sem_close(env->finish.mutex);
	sem_close(env->forks);
	sem_close(env->picking);
	sem_unlink("log");
	sem_unlink("finish");
	sem_unlink("forks");
	sem_unlink("terminated");
	sem_unlink("picking");
	free(env->philos);
}
