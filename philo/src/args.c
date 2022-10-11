/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:40:00 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/11 16:53:24 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (rules->number == 0 || rules->die == 0 || \
		rules->eat == 0 || rules->sleep == 0)
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
