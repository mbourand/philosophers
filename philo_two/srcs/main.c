/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:12 by user42            #+#    #+#             */
/*   Updated: 2020/12/01 03:09:47 by user42           ###   ########.fr       */
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
	sem_unlink("forks");
	sem_unlink("picking");
	sem_unlink("fed");
	env->log_mutex = sem_open("log", O_CREAT | O_EXCL, 0644, 1);
	env->finish.mutex = sem_open("finish", O_CREAT | O_EXCL, 0644, 1);
	env->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, env->stngs.philo_nb);
	env->picking = sem_open("picking", O_CREAT | O_EXCL, 0644, 1);
	env->fed.mutex = sem_open("fed", O_CREAT | O_EXCL, 0644, 1);
	env->fed.val = 0;
	env->finish.val = 0;
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
	t_philo	*philo;
	char	buf[256];

	philo = env->philos + (i - 1);
	philo->env = env;
	philo->id = i;
	ft_strjoin("last_eat", ft_itoa(i, buf), philo->lsteat_name);
	sem_unlink(philo->lsteat_name);
	philo->last_eat.mutex = sem_open(philo->lsteat_name, O_CREAT | O_EXCL, 0777, 1);
	philo->last_eat.val = get_time();
	ft_strjoin("meals", buf, philo->meals_name);
	sem_unlink(philo->meals_name);
	philo->meals.mutex = sem_open(philo->meals_name, O_CREAT | O_EXCL, 0777, 1);
	philo->meals.val = 0;
	pthread_create(&philo->thread, NULL, &process_philosopher, philo);
	philo->set_fed_mutex = 0;
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
	int		i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (1);
	if (!get_args(ac, av, &env) || !init_env(&env)
			|| !create_philosophers(&env))
		return (1);
	wait_philosophers(&env);
	while (i < env.stngs.philo_nb)
		pthread_join(env.philos[i++].thread, NULL);
	free_env(&env);
	return (0);
}
