/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 13:40:00 by gbaumgar          #+#    #+#             */
/*   Updated: 2022/10/11 14:34:01 by gbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	args_loader(char **argv, t_philo **philo)
{
	(*philo)->rules.number = ft_atoi(argv[1]);
	(*philo)->rules.die = ft_atoi(argv[2]);
	(*philo)->rules.eat = ft_atoi(argv[3]);
	(*philo)->rules.sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*philo)->rules.full = ft_atoi(argv[5]);
	else
		(*philo)->rules.full = 0;
	if ((*philo)->rules.number == 0 || (*philo)->rules.die == 0 || \
		(*philo)->rules.eat == 0 || (*philo)->rules.sleep == 0)
		return (-1);
	return (0);
}

int	args_handler(int argc, char **argv, t_philo **philo)
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
	if (args_loader(argv, philo))
	{
		ft_putstr_fd("Mandatory args cannot be 0\n", 2);
		return (-3);
	}
	return (0);
}
