/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:45:33 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/21 17:18:42 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_rules	t_rules;

struct s_rules
{
	pthread_mutex_t	lock;
	long int		time;	
	int				number;
	int				die;
	int				eat;
	int				sleep;
	int				full;
	int				finish;
};

struct s_philo
{
	t_rules			*rules;
	pthread_t		*thread;
	int				id;
	long unsigned	last_meal;
	int				meals_eaten;
	int				fork_state;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	lock;
	t_philo			*next_philo;
};

//	args.c
int				args_loader(char **argv, t_rules *rules);
int				args_handler(int argc, char **argv, t_rules *rules);
t_philo			*philo_init(t_rules *rules);

//	thread.c
void			*philosopher(void *args);

//	utils.c
size_t			ft_strlen(const char *s);
int				ft_isdigit(int c);
int				ft_isanumber(char *str);
int				ft_atoi(const char *str);
void			ft_putstr_fd(char *s, int fd);

//	misc.c
long unsigned	atm(void);
void			ft_sleep(long delay);
int				philo_check(t_philo *philo);
void			philo_end(t_philo *philo, t_rules rules);

#endif