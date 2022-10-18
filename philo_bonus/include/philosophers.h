/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:45:33 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/18 18:27:35 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <semaphore.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h> 
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_rules	t_rules;

struct s_rules
{
	long int		time;	
	int				number;
	int				die;
	int				eat;
	int				sleep;
	int				full;
	int				finish;
	sem_t			*forks;
	sem_t			*checker;
};

struct s_philo
{
	t_rules			*rules;
	pid_t			pid;
	int				id;
	long unsigned	last_meal;
	int				meals_eaten;
	int				ded;
	t_philo			*next_philo;
};

//	args.c
int				args_loader(char **argv, t_rules *rules);
int				args_handler(int argc, char **argv, t_rules *rules);
t_philo			*philo_init(t_rules *rules);

//	thread.c
void			philosopher(t_philo *philo);

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