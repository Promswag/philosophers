/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:45:33 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/11 16:51:03 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_rules
{
	pthread_mutex_t	*lock;
	long int		time;	
	int				number;
	int				die;
	int				eat;
	int				sleep;
	int				full;
}	t_rules;

typedef struct s_philo
{
	t_rules			*rules;
	pthread_t		*thread;
	int				id;
}	t_philo;

//	args.c
int		args_loader(char **argv, t_rules *rules);
int		args_handler(int argc, char **argv, t_rules *rules);

//	utils.c
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_isanumber(char *str);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);

#endif