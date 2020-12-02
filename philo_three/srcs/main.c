/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:12 by user42            #+#    #+#             */
/*   Updated: 2020/12/02 16:25:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		main(int ac, char **av)
{
	t_env		env;
	pthread_t	thread;
	int			i;

	i = 0;
	if (ac != 5 && ac != 6)
		return (1);
	if (!get_args(ac, av, &env) || !init_env(&env)
			|| !create_philosophers(&env))
		return (1);
	pthread_create(&thread, NULL, &wait_philosophers_fed, &env);
	while (i < env.stngs.philo_nb)
		sem_wait(env.philos[i++].catch_stop);
	sem_post(env.log_mutex);
	i = 0;
	while (i < env.stngs.philo_nb)
	{
		waitpid(env.philos[i++].pid, NULL, 0);
		sem_post(env.fed);
	}
	pthread_join(thread, NULL);
	free_env(&env);
	return (0);
}
