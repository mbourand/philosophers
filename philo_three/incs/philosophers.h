/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:30 by user42            #+#    #+#             */
/*   Updated: 2020/12/10 03:41:18 by user42           ###   ########.fr       */
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
# include <signal.h>
# include <wait.h>

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
	sem_t			*picking;
	sem_t			*fed;
	sem_t			*stop;
	sem_t			*lock;
}				t_env;

typedef struct	s_philo
{
	t_env			*env;
	pthread_t		thread;
	pthread_t		death_thread;
	int				id;
	char			lsteat_name[50];
	t_mutexint		last_eat;
	char			meals_name[50];
	char			catch_name[50];
	t_mutexint		meals;
	sem_t			*catch_stop;
	int				set_fed_mutex;
	pid_t			pid;
}				t_philo;

void			*process_philosopher(void *philo);
void			phil_wait(long micro);
void			phil_eat(t_philo *philo);
void			phil_sleep(t_philo *philo);
void			phil_think(t_philo *philo);
int				phil_die(t_philo *philo);
void			phil_fork(t_philo *philo);
int				starved(t_philo *philo);
void			log_philo(t_philo *philo, int t, char *msg);
int				ft_atoui(const char *s);
size_t			ft_strlen(char *s);
int				get_time(void);
void			*wait_philosophers_death(void *param);
void			*wait_philosophers_fed(void *param);
int				can_eat(t_philo *philo);
void			free_env(t_env *env);
void			log_philo_force(t_philo *philo, int t, char *msg);
void			wait_fork(t_philo *philo, int index);
char			*ft_strcpy(char *dest, char *src);
int				ft_numlen(unsigned int i);
char			*ft_itoa(unsigned int nb, char *buf);
void			print_log(int t, int id, char *msg);
int				get_mutexint(t_mutexint *mi);
void			set_mutexint(t_mutexint *mi, int val);
void			inc_mutexint(t_mutexint *mi);
char			*ft_strjoin(char *s1, char *s2, char *buf);
int				init_env(t_env *env);
int				init_philosopher(t_env *env, int i);
int				create_philosophers(t_env *env);
int				get_args(int ac, char **av, t_env *env);
int				is_finished(t_philo *philo);
void			free_sem(sem_t *sem, char *name);

#endif
