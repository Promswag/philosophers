/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:45:33 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/11 14:34:00 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_rules
{
	int	number;
	int	die;
	int	eat;
	int	sleep;
	int	full;
}	t_rules;

typedef struct s_philo
{
	t_rules		rules;
	pthread_t	*threads;
}	t_philo;

//	args.c
int		args_loader(char **argv, t_philo **philo);
int		args_handler(int argc, char **argv, t_philo **philo);

//	utils.c
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_isanumber(char *str);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);

#endif