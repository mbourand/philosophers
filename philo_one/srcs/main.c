/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:12 by user42            #+#    #+#             */
/*   Updated: 2020/11/30 19:27:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		init_env(t_env *env)
{
	int i;

	i = 0;
	if (!(env->philos = malloc(sizeof(t_philo) * env->stngs.philo_nb)))
		return (0);
	if (!(env->forks = malloc(sizeof(t_fork) * env->stngs.philo_nb)))
	{
		free(env->philos);
		return (0);
	}
	env->start_time = get_time();
	pthread_mutex_init(&env->log_mutex, NULL);
	pthread_mutex_init(&env->finish.mutex, NULL);
	pthread_mutex_init(&env->fed.mutex, NULL);
	while (i < env->stngs.philo_nb)
	{
		pthread_mutex_init(&env->forks[i].mutex, NULL);
		pthread_mutex_init(&env->philos[i].lock, NULL);
		pthread_mutex_init(&env->forks[i].last_philo.mutex, NULL);
		env->forks[i].last_philo.val = -1;
		i++;
	}
	env->finish.val = 0;
	env->fed.val = 0;
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
	pthread_mutex_init(&philo->last_eat.mutex, NULL);
	philo->last_eat.val = get_time();
	philo->l_fork = (i == 0 ? (int)env->stngs.philo_nb - 1 : (i - 1));
	philo->r_fork = i % env->stngs.philo_nb;
	pthread_mutex_init(&philo->meals.mutex, NULL);
	philo->meals.val = 0;
	philo->set_fed_mutex = 0;
	pthread_create(&philo->thread, NULL, &process_philosopher, philo);
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
