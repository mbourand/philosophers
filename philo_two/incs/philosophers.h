/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:30 by user42            #+#    #+#             */
/*   Updated: 2020/12/01 02:00:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <fcntl.h>

struct s_philo;

typedef struct	s_mutexint
{
	sem_t		*mutex;
	int			val;
}				t_mutexint;

typedef struct	s_settings
{
	int		philo_nb;
	int		die_time;
	int		sleep_time;
	int		eat_time;
	int		max_eat;
}				t_settings;

typedef struct	s_env
{
	t_settings		stngs;
	sem_t			*log_mutex;
	struct s_philo	*philos;
	sem_t			*forks;
	int				start_time;
	t_mutexint		finish;
	t_mutexint		fed;
	sem_t			*picking;
}				t_env;

typedef struct	s_philo
{
	t_env			*env;
	pthread_t		thread;
	int				id;
	char			lsteat_name[50];
	t_mutexint		last_eat;
	char			meals_name[50];
	t_mutexint		meals;
	int				set_fed_mutex;
}				t_philo;

void	*process_philosopher(void *philo);
void	phil_wait(long micro);
void	phil_eat(t_philo *philo);
void	phil_sleep(t_philo *philo);
void	phil_think(t_philo *philo);
void	phil_die(t_philo *philo);
void	phil_fork(t_philo *philo);
int		starved(t_philo *philo);
void	log_philo(t_philo *philo, int t, char *msg);
int		ft_atoui(const char *s);
size_t	ft_strlen(char *s);
int		get_time(void);
int		wait_philosophers(t_env *env);
int		can_eat(t_philo *philo);
void	free_env(t_env *env);
void	log_philo_force(t_philo *philo, int t, char *msg);
void	wait_fork(t_philo *philo, int index);
char	*ft_strcpy(char *dest, char *src);
int		ft_numlen(unsigned int i);
char	*ft_itoa(unsigned int nb, char *buf);
void	print_log(int t, int id, char *msg);
int		is_fed(t_philo *philo);
int		get_mutexint(t_mutexint* mi);
void	set_mutexint(t_mutexint* mi, int val);
void	inc_mutexint(t_mutexint* mi);
char	*ft_strjoin(char *s1, char *s2, char *buf);

#endif
