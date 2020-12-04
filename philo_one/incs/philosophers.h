/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:30 by user42            #+#    #+#             */
/*   Updated: 2020/12/03 15:02:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

struct s_philo;

typedef struct	s_mutexint
{
	pthread_mutex_t	mutex;
	int				val;
}				t_mutexint;

typedef struct	s_fork
{
	pthread_mutex_t	mutex;
	t_mutexint		last_philo;
}				t_fork;

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
	pthread_mutex_t	log_mutex;
	struct s_philo	*philos;
	t_fork			*forks;
	int				start_time;
	t_mutexint		finish;
	t_mutexint		fed;
}				t_env;

typedef struct	s_philo
{
	t_env			*env;
	pthread_t		thread;
	pthread_mutex_t lock;
	int				id;
	t_mutexint		last_eat;
	t_mutexint		meals;
	int				l_fork;
	int				r_fork;
	int				set_fed_mutex;
}				t_philo;

void			*process_philosopher(void *philo);
void			phil_wait(long micro);
void			phil_eat(t_philo *philo);
void			phil_sleep(t_philo *philo);
void			phil_think(t_philo *philo);
void			phil_die(t_philo *philo);
void			phil_fork(t_philo *philo);
int				starved(t_philo *philo);
void			log_philo(t_philo *philo, int t, char *msg);
int				ft_atoui(const char *s);
size_t			ft_strlen(char *s);
int				get_time(void);
int				wait_philosophers(t_env *env);
int				can_eat(t_philo *philo);
void			free_env(t_env *env);
void			log_philo_force(t_philo *philo, int t, char *msg);
void			wait_fork(t_philo *philo, int index);
char			*ft_strcpy(char *dest, char *src);
int				ft_numlen(unsigned int i);
char			*ft_itoa(unsigned int nb, char *buf);
void			print_log(int t, int id, char *msg);
int				is_fed(t_philo *philo);
int				get_mutexint(t_mutexint *mi);
void			set_mutexint(t_mutexint *mi, int val);
void			inc_mutexint(t_mutexint *mi);

#endif
