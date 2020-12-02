/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:30 by user42            #+#    #+#             */
/*   Updated: 2020/11/12 18:34:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <pthread.h>
# include <wait.h>
# include <sys/types.h>
# include <signal.h>

# define FED 1
# define DEAD 0

struct s_philo;

typedef struct	s_mutexint
{
	sem_t	*mutex;
	int		val;
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
	sem_t			*picking;
	sem_t			*one_dead;
	int				start_time;
}				t_env;

typedef struct	s_philo
{
	t_env		*env;
	pid_t		thread;
	pthread_t	death_thread;
	int			id;
	t_mutexint	last_eat;
	t_mutexint	meals;
	t_mutexint	dead;
	sem_t		*ate;
	char		dead_name[256];
	char		meals_name[256];
	char		lsteat_name[256];
	char		ate_name[256];
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
void			ft_putnbr(int i);
void			ft_putchar(char c);
int				get_time(void);
void			wait_philosophers(t_env *env);
int				can_eat(t_philo *philo);
void			free_env(t_env *env);
void			log_philo_force(t_philo *philo, int t, char *msg);
void			wait_fork(t_philo *philo, int index);
char			*ft_strjoin_buf(char *s1, char *s2, char *res);
char			*ft_itoa(unsigned int nb);
int				is_finished(t_philo *philo);
void			*check_philo_death(void *philo);
int				init_env(t_env *env);
int				get_args(int ac, char **av, t_env *env);
void			create_fork(t_philo *philo);
int				init_philosopher(t_env *env, int i);
int				create_philosophers(t_env *env);
void			print_log(int t, int id, char *msg);
int				ft_numlen(unsigned int i);
char			*ft_itoa_buf(unsigned int nb, char *buf);
int				free_vars(t_philo *philo);
int				is_fed(t_philo *philo);
void			*wait_fed(void* param);

#endif
