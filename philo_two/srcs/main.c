/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:12 by user42            #+#    #+#             */
/*   Updated: 2020/11/05 16:11:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		init_env(t_env *env)
{
	if (!(env->philos = malloc(sizeof(t_philo) * env->stngs.philo_nb)))
		return (0);
	env->start_time = get_time();
	sem_unlink("log");
	sem_unlink("finish");
	sem_unlink("terminated");
	sem_unlink("forks");
	sem_unlink("picking");
	env->log_mutex = sem_open("log", O_CREAT, 0777, 1);
	env->finish.mutex = sem_open("finish", O_CREAT, 0777, 1);
	env->terminated.mutex = sem_open("terminated", O_CREAT, 0777, 1);
	env->forks = sem_open("forks", O_CREAT, 0777, env->stngs.philo_nb);
	env->picking = sem_open("picking", O_CREAT, 0777, 1);
	env->finish.val = 0;
	env->terminated.val = 0;
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

int		init_philosopher(t_env *env, int i)
{
	t_philo *philo;

	philo = env->philos + (i - 1);
	philo->env = env;
	philo->id = i;
	philo->lsteat_name = ft_strjoin("last_eat", ft_itoa(i));
	sem_unlink(philo->lsteat_name);
	philo->last_eat.mutex = sem_open(philo->lsteat_name, O_CREAT, 0777, 1);
	philo->last_eat.val = get_time();
	philo->l_fork = (i == 0 ? (int)env->stngs.philo_nb - 1 : (i - 1));
	philo->r_fork = i % env->stngs.philo_nb;
	philo->meals_name = ft_strjoin("meals", ft_itoa(i));
	sem_unlink(philo->meals_name);
	philo->meals.mutex = sem_open(philo->meals_name, O_CREAT, 0777, 1);
	philo->meals.val = 0;
	pthread_create(&philo->thread, NULL, &process_philosopher, philo);
	pthread_detach(philo->thread);
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

int		main(int ac, char **av)
{
	t_env	env;

	if (ac != 5 && ac != 6)
		return (1);
	if (!get_args(ac, av, &env) || !init_env(&env)
			|| !create_philosophers(&env))
		return (1);
	wait_philosophers(&env);
	sem_wait(env.terminated.mutex);
	while (env.terminated.val != env.stngs.philo_nb)
	{
		sem_post(env.terminated.mutex);
		phil_wait(10);
		sem_wait(env.terminated.mutex);
	}
	sem_post(env.terminated.mutex);
	free_env(&env);
	return (0);
}
