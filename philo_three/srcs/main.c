/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:12 by user42            #+#    #+#             */
/*   Updated: 2020/11/13 13:21:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		main(int ac, char **av)
{
	t_env		env;
	pthread_t	fed_thread;

	if (ac != 5 && ac != 6)
		return (1);
	if (!get_args(ac, av, &env) || !init_env(&env)
			|| !create_philosophers(&env))
		return (1);
	if (env.stngs.max_eat != 2147483647)
	{
		pthread_create(&fed_thread, NULL, &wait_fed, &env);
		pthread_detach(fed_thread);
	}
	wait_philosophers(&env);
	free_env(&env);
	return (0);
}
