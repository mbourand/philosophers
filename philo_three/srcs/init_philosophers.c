/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:12 by user42            #+#    #+#             */
/*   Updated: 2020/11/12 18:34:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		init_env(t_env *env)
{
	if (!(env->philos = malloc(sizeof(t_philo) * env->stngs.philo_nb)))
		return (0);
	env->start_time = get_time();
	sem_unlink("log");
	sem_unlink("forks");
	sem_unlink("picking");
	sem_unlink("one_dead");
	env->log_mutex = sem_open("log", O_CREAT | O_EXCL, 0770, 1);
	env->forks = sem_open("forks", O_CREAT | O_EXCL, 0770, env->stngs.philo_nb);
	env->picking = sem_open("picking", O_CREAT | O_EXCL, 0770, 1);
	env->one_dead = sem_open("one_dead", O_CREAT | O_EXCL, 0770, 0);
	return (1);
}

int		get_args(int ac, char **av, t_env *env)
{
	int	i;
	int	**vars;
	int	tmp;

	vars = (int *[]) { &(env->stngs.philo_nb), &(env->stngs.die_time),
		&(env->stngs.eat_time), &(env->stngs.sleep_time),
		&(env->stngs.max_eat) };
	i = 0;
	while (++i < ac)
	{
		tmp = (int)ft_atoui(av[i]);
		if (tmp < 0)
			return (0);
		*(vars[i - 1]) = tmp;
	}
	if (ac != 6)
		env->stngs.max_eat = 2147483647;
	return (1);
}

void	create_fork(t_philo *philo)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		pthread_create(&philo->death_thread, NULL, &check_philo_death, philo);
		pthread_detach(philo->death_thread);
		process_philosopher(philo);
	}
	else
		philo->thread = pid;
}

int		init_philosopher(t_env *env, int i)
{
	t_philo *philo;
	char	buff[256];

	philo = env->philos + (i - 1);
	philo->env = env;
	philo->id = i;
	ft_strjoin_buf("last_eat", ft_itoa_buf(i, buff), philo->lsteat_name);
	sem_unlink(philo->lsteat_name);
	philo->last_eat.mutex = sem_open(philo->lsteat_name, O_CREAT, 0770, 1);
	philo->last_eat.val = get_time();
	ft_strjoin_buf("meals", buff, philo->meals_name);
	sem_unlink(philo->meals_name);
	philo->meals.mutex = sem_open(philo->meals_name, O_CREAT, 0770, 1);
	philo->meals.val = 0;
	ft_strjoin_buf("dead", buff, philo->dead_name);
	sem_unlink(philo->dead_name);
	philo->dead.mutex = sem_open(philo->dead_name, O_CREAT, 0770, 1);
	philo->dead.val = 0;
	ft_strjoin_buf("ate", buff, philo->ate_name);
	sem_unlink(philo->ate_name);
	philo->ate = sem_open(philo->ate_name, O_CREAT, 0770, 0);
	create_fork(philo);
	return (1);
}

int		create_philosophers(t_env *env)
{
	int i;

	i = 1;
	while (i <= env->stngs.philo_nb)
	{
		if (!init_philosopher(env, i))
			return (0);
		i += 2;
		phil_wait(200);
	}
	phil_wait(5000);
	i = 2;
	while (i <= env->stngs.philo_nb)
	{
		if (!init_philosopher(env, i))
			return (0);
		i += 2;
		phil_wait(200);
	}
	return (1);
}
