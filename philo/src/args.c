/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:40:00 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/13 13:46:21 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	args_loader(char **argv, t_rules *rules)
{
	rules->number = ft_atoi(argv[1]);
	rules->die = ft_atoi(argv[2]);
	rules->eat = ft_atoi(argv[3]);
	rules->sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->full = ft_atoi(argv[5]);
	else
		rules->full = 0;
	pthread_mutex_init(&rules->lock, NULL);
	if (!rules->number || !rules->die || \
		!rules->eat || !rules->sleep)
		return (-1);
	return (0);
}

int	args_handler(int argc, char **argv, t_rules *rules)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Too few/many arguments\n", 2);
		return (-1);
	}
	while (--argc)
	{
		if (!ft_isanumber(argv[argc]))
		{
			ft_putstr_fd("Args must be numbers\n", 2);
			return (-2);
		}
	}
	if (args_loader(argv, rules))
	{
		ft_putstr_fd("Mandatory args cannot be 0\n", 2);
		return (-3);
	}
	return (0);
}

t_philo	*philo_init(t_rules *rules)
{
	t_philo			*philo;
	int				i;

	philo = malloc(sizeof(t_philo) * rules->number);
	i = -1;
	while (++i < rules->number)
	{
		philo[i].id = i + 1;
		philo[i].rules = rules;
		philo[i].fork_state = 1;
		philo[i].ded = 0;
		pthread_mutex_init(&philo[i].left_fork, NULL);
		pthread_mutex_init(&philo[i].lock, NULL);
		philo[i].thread = malloc(sizeof(pthread_t *));
	}
	i = -1;
	while (++i < rules->number - 1)
		philo[i].next_philo = &philo[i + 1];
	philo[i].next_philo = &philo[0];
	rules->time = atm();
	rules->finish = 0;
	return (philo);
}
